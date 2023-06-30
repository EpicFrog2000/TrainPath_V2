#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QString first, QString second, QWidget *parent = nullptr);
    ~GLWidget();

public slots:
    void cleanup();

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    void setupVertexAttribs(QOpenGLBuffer& buffer); // Added reference parameter
    bool m_core;
    static bool m_transparent;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer stacjeVbo;
    QOpenGLBuffer pathVbo;
    QOpenGLBuffer stacjeKolorVbo;
    QOpenGLBuffer pathKolorVbo;
    QMatrix4x4 m_world;
    QMatrix4x4 m_proj;
    GLsizei vertexes = 0;
    QOpenGLShaderProgram *m_program = nullptr;

    // Additional member variables to store values from another class
    QString first;
    QString second;
};
