#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <vector>
#include <QPlainTextEdit>

#include "Contact_With_DB/contact_with_db.hpp"
#include "destination_functions/Coordinates_Calculations.hpp"
#include "Drawing_Map/Map_Draw.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)



class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QString first, QString second, int odchylenie , QWidget *parent = nullptr);
    ~GLWidget();

    static QPlainTextEdit *termianlArea();

public slots:
    void cleanup();

protected:
    void initializeGL() override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    void setupVertexAttribs(QOpenGLBuffer& buffer);
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
    bool clicked;

    QString first;
    QString second;
    int odchylenie;

    //Yeah
    std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
    std::vector<std::pair<int, int>> firstStation = GetOneStationCoords(first.toStdString(), allStations);
    std::vector<std::pair<int, int>> secondStation = GetOneStationCoords(second.toStdString(), allStations);
    std::set<std::pair<int, int>> sortedStations = SortStationsByDistance(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation), odchylenie), firstStation, secondStation);
    std::vector<std::pair<int, int>> PathPoints = GetPathBetweenMultipleStations(sortedStations);
};
