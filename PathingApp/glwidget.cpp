#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QString first, QString second, int odchylenie, QWidget *parent)
    : QOpenGLWidget(parent), first(first), second(second), odchylenie(odchylenie)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
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
    "// Input vertex data, different for all executions of this shader.\n"
    "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
    "out vec3 fragmentColor;\n"
    "void main() {\n"
    "    // Invert the Y coordinate\n"
    "    gl_Position.xyz = vertexPosition_modelspace;\n"
    "    gl_Position.w = 0.5;\n"
    "    gl_Position.x -= 0.5;\n"
    "    gl_Position.y += 0.5;\n"
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
            x - 0.004f, -y - 0.004f, 0.0f,
            x + 0.004f, -y - 0.004f, 0.0f,
            x - 0.004f, -y + 0.004f, 0.0f,
            x + 0.004f, -y - 0.004f, 0.0f,
            x + 0.004f, -y + 0.004f, 0.0f,
            x - 0.004f, -y + 0.004f, 0.0f,
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

    additionalData.clear();
    additionalColorData.clear();

    for (const auto &path : PathPoints)
    {
        pathVbo.bind();
        x = static_cast<float>(path.first) / 100;
        y = static_cast<float>(path.second) / 100;
        vertexes += 6;
        GLfloat newData[] = {
            x - 0.004f, -y - 0.004f, 0.0f,
            x + 0.004f, -y - 0.004f, 0.0f,
            x - 0.004f, -y + 0.004f, 0.0f,
            x + 0.004f, -y - 0.004f, 0.0f,
            x + 0.004f, -y + 0.004f, 0.0f,
            x - 0.004f, -y + 0.004f, 0.0f,
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

    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(45.0f, width() / height(), 0.1f, 100.0f);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0f, 0.0f, -1.0f);

    QMatrix3x3 normalMatrix = modelViewMatrix.normalMatrix();

    QVector3D lightPosition(0.0f, 0.0f, 1.0f);

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

void GLWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (clicked)
        {
            clicked = false;
            double xpos = event->position().x()  / 1000.0;
            double ypos = event->position().y()  / 1000.0;
            for (const auto &station : allStations)
            {
                double stationX = static_cast<double>(station.second.first) / 100.0;
                double stationY = static_cast<double>(station.second.second) / 100.0;
                if (xpos >= stationX - 0.008 && xpos <= stationX + 0.008 &&
                    ypos >= stationY - 0.008 && ypos <= stationY + 0.008)
                {
                    qDebug() << "station name:" << station.first << ", x, y:" << stationX << ", " << stationY;
                    //change later to display info in applications terminal area
                    break;
                }
            }
        }
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        clicked = true;
    }
}
