#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

#include "Contact_With_DB/contact_with_db.hpp"
#include "destination_functions/Coordinates_Calculations.hpp"
#include "Drawing_Map/Map_Draw.hpp"

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QString first, QString second, int odchylenie, QWidget *parent)
    : QOpenGLWidget(parent), first(first), second(second), odchylenie(odchylenie)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }
}

GLWidget::~GLWidget()
{
    cleanup();
}

void GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    stacjeVbo.destroy();
    pathVbo.destroy();
    stacjeKolorVbo.destroy();
    pathKolorVbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
    QObject::disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
}


const char *vertexShaderSourceCore =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
    "out vec3 fragmentColor;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "uniform vec3 lightPos;\n"
    "void main() {\n"
    "    gl_Position = projMatrix * mvMatrix * vec4(vertexPosition_modelspace - 0.5, 1.0);\n"
    "    fragmentColor = vertexColor;\n"
    "}\n";

const char *fragmentShaderSourceCore =
    "#version 330 core\n"
    "in vec3 fragmentColor;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(fragmentColor, 1.0);\n"
    "}\n";

void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
    m_program->bindAttributeLocation("vertexPosition_modelspace", 0);
    m_program->bindAttributeLocation("vertexColor", 1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();

    std::vector<std::pair<int, int>> firstStation = GetOneStationCoords(first.toStdString(), allStations);
    std::vector<std::pair<int, int>> secondStation = GetOneStationCoords(second.toStdString(), allStations);
    std::set<std::pair<int, int>> sortedStations = SortStationsByDistance(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation), odchylenie), firstStation, secondStation);
    std::vector<std::pair<int, int>> PathPoints = GetPathBetweenMultipleStations(sortedStations);

    // Setup our vertex buffer object.
    stacjeVbo.create();
    pathVbo.create();
    stacjeKolorVbo.create();
    pathKolorVbo.create();

    std::vector<GLfloat> additionalData;
    std::vector<GLfloat> additionalColorData;
    float x = 0.0f / 100;
    float y = 0.0f / 100;

    vertexes = 0;
    for (const auto &station : allStations)
    {
        stacjeVbo.bind();
        x = static_cast<float>(station.second.first) / 100;
        y = static_cast<float>(station.second.second) / 100;
        vertexes += 6;
        GLfloat newData[] = {
            x - 0.004f,	y - 0.004f,	0.0f,
            x + 0.004f,	y - 0.004f,	0.0f,
            x - 0.004f,	y + 0.004f,	0.0f,

            x + 0.004f,	y - 0.004f,	0.0f,
            x + 0.004f,	y + 0.004f,	0.0f,
            x - 0.004f,	y + 0.004f,	0.0f,
        };
        additionalData.insert(additionalData.end(), newData, newData + sizeof(newData) / sizeof(newData[0]));

        stacjeKolorVbo.bind();
        GLfloat newColorData[] = {
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
        };
        additionalColorData.insert(additionalColorData.end(), newColorData, newColorData + sizeof(newColorData) / sizeof(newColorData[0]));
    }
    stacjeKolorVbo.bind();
    stacjeKolorVbo.allocate(additionalColorData.data(), additionalColorData.size() * sizeof(GLfloat));
    setupVertexAttribs(stacjeKolorVbo);

    stacjeVbo.bind();
    stacjeVbo.allocate(additionalData.data(), additionalData.size() * sizeof(GLfloat));
    setupVertexAttribs(stacjeVbo);
    //----------------------------------------------------------------------------------------------------------------------------------
    for (const auto &path : PathPoints)
    {
        pathVbo.bind();
        x = static_cast<float>(path.first) / 100;
        y = static_cast<float>(path.second) / 100;
        vertexes += 6;
        GLfloat newData[] = {
            x - 0.004f, y - 0.004f, 0.0f,
            x + 0.004f, y - 0.004f, 0.0f,
            x - 0.004f, y + 0.004f, 0.0f,

            x + 0.004f,	y - 0.004f,	0.0f,
            x + 0.004f,	y + 0.004f,	0.0f,
            x - 0.004f,	y + 0.004f,	0.0f,
        };
        additionalData.insert(additionalData.end(), newData, newData + sizeof(newData) / sizeof(newData[0]));

        pathKolorVbo.bind();
        GLfloat newColorData[] = {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
        };
        additionalColorData.insert(additionalColorData.end(), newColorData, newColorData + sizeof(newColorData) / sizeof(newColorData[0]));
    }

    pathKolorVbo.bind();
    pathKolorVbo.allocate(additionalColorData.data(), additionalColorData.size() * sizeof(GLfloat));
    setupVertexAttribs(pathKolorVbo);

    pathVbo.bind();
    pathVbo.allocate(additionalData.data(), additionalData.size() * sizeof(GLfloat));
    setupVertexAttribs(pathVbo);
    m_program->release();
}

void GLWidget::setupVertexAttribs(QOpenGLBuffer& buffer)
{
    buffer.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    buffer.release();
}
void GLWidget::paintGL()
{
    // ...

    // Define and set the projection matrix
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(45.0f, width() / height(), 0.1f, 100.0f);

    // Define and set the model-view matrix
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0f, 0.0f, -1.0f);

    // Define and set the normal matrix
    QMatrix3x3 normalMatrix = modelViewMatrix.normalMatrix();

    // Define and set the light position
    QVector3D lightPosition(0.0f, 0.0f, 1.0f);

    // ...

    m_program->setUniformValue("projMatrix", projectionMatrix);
    m_program->setUniformValue("mvMatrix", modelViewMatrix);
    m_program->setUniformValue("normalMatrix", normalMatrix);
    m_program->setUniformValue("lightPos", lightPosition);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    pathVbo.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    pathKolorVbo.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    m_program->setUniformValue("projMatrix", projectionMatrix);
    m_program->setUniformValue("mvMatrix", modelViewMatrix);
    m_program->setUniformValue("normalMatrix", normalMatrix);
    m_program->setUniformValue("lightPos", lightPosition);

    glDrawArrays(GL_TRIANGLES, 0, vertexes);

    stacjeVbo.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    stacjeKolorVbo.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    m_program->setUniformValue("projMatrix", projectionMatrix);
    m_program->setUniformValue("mvMatrix", modelViewMatrix);
    m_program->setUniformValue("normalMatrix", normalMatrix);
    m_program->setUniformValue("lightPos", lightPosition);

    glDrawArrays(GL_TRIANGLES, 0, vertexes);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    m_program->release();
}
