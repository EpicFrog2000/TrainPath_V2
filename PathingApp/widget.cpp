#include "widget.h"
#include "glwidget.h"
#include "Contact_With_DB/contact_with_db.hpp"
#include <algorithm>
#include <QDebug>

GLWidget *glWidget;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Train Pathing App");

    // Create the layouts
    vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    QGridLayout *grid = new QGridLayout();

    // Add the widgets to the grid layout
    grid->addWidget(createOptionsGroup(), 0, 0);
    grid->addWidget(createInputGroup(), 1, 0);

    // Add the grid layout to the horizontal layout
    hbox->addLayout(grid);

    // Create the text area and terminal area widgets
    QPlainTextEdit *terminalArea = termianlArea();

    glWidget = new GLWidget("Warszawa","Warszawa", 0);
    glWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    terminalArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    glWidget->setMinimumHeight(0);
    terminalArea->setMinimumHeight(0);
    vbox->addWidget(glWidget, 8); // Set the stretch factor to 8 (80% of the available height)
    vbox->addWidget(terminalArea, 2); // Set the stretch factor to 2 (20% of the available height)

    // Add the vertical layout to the horizontal layout
    hbox->addLayout(vbox);

    // Set the main layout for the widget
    setLayout(hbox);

    setFixedHeight(800);
    setFixedWidth(1280);
}

Widget::~Widget()
{
}

QGroupBox *Widget::createOptionsGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Opcje"));
    groupBox->setFixedWidth(200);
    QVBoxLayout *vbox = new QVBoxLayout();
    QLabel *lb1 = new QLabel("ODCHYLENIE:  ");
    spin = new QSpinBox;
    spin->setFocusPolicy(Qt::TabFocus);
    QHBoxLayout *hbox1 = new QHBoxLayout();
    hbox1->addWidget(lb1);
    hbox1->addWidget(spin);
    vbox->addLayout(hbox1);

    groupBox->setLayout(vbox);
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

    //textd = new QLineEdit();
    //textz = new QLineEdit();
    QPushButton *button = new QPushButton("Start");
    //textd->setFixedHeight(30);
    //textz->setFixedHeight(30);
    start = new QComboBox;
    end = new QComboBox;

    //get allstations
    std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
    //sort them alphabetically
    std::sort(allStations.begin(), allStations.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.first < rhs.first;
              });
    for (const auto& station : allStations) {
        start->addItem(QString::fromStdString(station.first));
        end->addItem(QString::fromStdString(station.first));
    }

    hboxz->addWidget(lb1,2);
    hboxz->addWidget(start,8);

    hboxd->addWidget(lb2,2);
    hboxd->addWidget(end,8);

    vbox->addLayout(hboxz);
    vbox->addLayout(hboxd);
    vbox->addWidget(button);
    groupBox->setLayout(vbox);
    groupBox->setFixedHeight(300);
    connect(button, &QPushButton::clicked, this, &Widget::buttonClicked);
    return groupBox;
}

QPlainTextEdit *Widget::termianlArea()
{
    textArea = new QPlainTextEdit();
    //textArea->setReadOnly(true);
    textArea->setMinimumHeight(50);

    return textArea;
}

void Widget::buttonClicked()
{
    QString first = start->currentText();
    QString second = end->currentText();


    // Remove the existing GLWidget from the layout
    vbox->removeWidget(glWidget);
    delete glWidget;

    // Recreate the GLWidget
    glWidget = new GLWidget(first, second, spin->value());
    glWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Add the new GLWidget back to the layout
    vbox->insertWidget(0, glWidget, 8);

    //TODO
    //Write path to console below glwidget (termianlArea)





}
