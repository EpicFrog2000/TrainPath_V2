#include "widget.h"
#include "Contact_With_DB/contact_with_db.hpp"
#include "destination_functions/Coordinates_Calculations.hpp"
#include "Drawing_Map/Map_Draw.hpp"
#include <vector>
#include <set>
#include <sstream>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Train Pathing App");

    // Create the layouts
    QHBoxLayout *hbox = new QHBoxLayout();
    QVBoxLayout *vbox = new QVBoxLayout();
    QGridLayout *grid = new QGridLayout();

    // Add the widgets to the grid layout
    grid->addWidget(createOptionsGroup(), 0, 0);
    grid->addWidget(createInputGroup(), 1, 0);

    // Add the grid layout to the horizontal layout
    hbox->addLayout(grid);

    // Create the text area and terminal area widgets
    QPlainTextEdit *textArea = textAreaDraw();
    QPlainTextEdit *terminalArea = termianlArea();

    // Set the size policies and stretch factors for the widgets
    textArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    terminalArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    textArea->setMinimumHeight(0);
    terminalArea->setMinimumHeight(0);


    vbox->addWidget(textArea, 8); // Set the stretch factor to 8 (80% of the available height)




    vbox->addWidget(terminalArea, 2); // Set the stretch factor to 2 (20% of the available height)

    // Add the vertical layout to the horizontal layout
    hbox->addLayout(vbox);

    // Set the main layout for the widget
    setLayout(hbox);

    setFixedHeight(800);
    setFixedWidth(1280);
}

QGroupBox *Widget::createOptionsGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Opcje"));
    groupBox->setFixedWidth(200);


    return groupBox;
}

QGroupBox *Widget::createInputGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Input"));
    groupBox->setFixedWidth(200);
    QLabel *lb1 = new QLabel("Z: ");
    QLabel *lb2 = new QLabel("Do: ");
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hboxz = new QHBoxLayout();
    QHBoxLayout *hboxd = new QHBoxLayout();

    textd->setFixedHeight(30);
    textz->setFixedHeight(30);

    hboxz->addWidget(lb1);
    hboxz->addWidget(textz);

    hboxd->addWidget(lb2);
    hboxd->addWidget(textd);

    vbox->addLayout(hboxz);
    vbox->addLayout(hboxd);
    vbox->addWidget(button);
    groupBox->setLayout(vbox);
    groupBox->setFixedHeight(300);
    connect(button, &QPushButton::clicked, this, &Widget::buttonClicked);
    return groupBox;
}

QPlainTextEdit *Widget::textAreaDraw()
{
    textArea->setReadOnly(true);
    QFont font("Monospace"); // Specify the font family name
    font.setPointSize(12); // Set the desired point size
    textArea->setFont(font);
    return textArea;
}

QPlainTextEdit *Widget::termianlArea()
{
    QPlainTextEdit *textArea = new QPlainTextEdit();
    //textArea->setReadOnly(true);
    textArea->setMinimumHeight(50);

    return textArea;
}

void Widget::buttonClicked()
{
    QString First = textz->toPlainText();
    QString Second = textd->toPlainText();

    // Create a stringstream to capture the output
    std::stringstream stream;

    // Redirect cout to the stringstream
    std::streambuf* oldBuffer = std::cout.rdbuf(stream.rdbuf());

    // Call the DrawMap function without modifying its implementation
    std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
    std::vector<std::pair<int, int>> firstStation = GetOneStationCoords(First.toStdString(), allStations);
    std::vector<std::pair<int, int>> secondStation = GetOneStationCoords(Second.toStdString(), allStations);
    const int ODCHYLENIE = 3;
    std::set<std::pair<int, int>> sortedStations = SortStationsByDistance(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation), ODCHYLENIE), firstStation, secondStation);
    DrawMap(allStations, GetPathBetweenMultipleStations(sortedStations));

    // Reset cout's stream buffer to the original one
    std::cout.rdbuf(oldBuffer);

    // Update the text in the textArea
    QString text = QString::fromStdString(stream.str()); // With consecutive spaces
    text = text.replace(' ', QChar(0x00A0)); // Replace regular spaces with non-breaking spaces
    textArea->setPlainText(text); // Set the modified text in the QPlainTextEdit
}

Widget::~Widget()
{
}

