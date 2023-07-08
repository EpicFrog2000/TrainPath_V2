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

    hbox = new QHBoxLayout();
    QVBoxLayout *leftPanel = new QVBoxLayout();

    leftPanel->addWidget(createOptionsGroup());
    leftPanel->addWidget(createInputGroup());

    hbox->addLayout(leftPanel);

    QPlainTextEdit *terminalArea = termianlArea();

    glWidget = new GLWidget("Warszawa","Warszawa", 0);
    glWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    terminalArea->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    glWidget->setFixedHeight(1000);
    glWidget->setFixedWidth(1000);
    terminalArea->setMinimumHeight(0);

    hbox->addWidget(glWidget);
    hbox->addWidget(terminalArea);

    setLayout(hbox);

    setFixedHeight(950);
}

Widget::~Widget()
{
}

QGroupBox *Widget::createOptionsGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Opcje"));
    groupBox->setFixedWidth(200);
    groupBox->setFixedHeight(400);
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
    groupBox->setFixedHeight(400);
    QLabel *lb1 = new QLabel("Z: ");
    QLabel *lb2 = new QLabel("Do: ");
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hboxz = new QHBoxLayout();
    QHBoxLayout *hboxd = new QHBoxLayout();

    QPushButton *button = new QPushButton("Start");
    start = new QComboBox;
    end = new QComboBox;

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
    textArea->setMinimumHeight(50);
    textArea->setMinimumWidth(200);
    return textArea;
}

void Widget::buttonClicked()
{
    QString first = start->currentText();
    QString second = end->currentText();

    hbox->removeWidget(glWidget);
    delete glWidget;

    glWidget = new GLWidget(first, second, spin->value());
    glWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    glWidget->setFixedHeight(1000);
    glWidget->setFixedWidth(1000);
    // Add the new GLWidget back to the layout
    hbox->insertWidget(1, glWidget);

    //TODO
    //Write path to console below glwidget (termianlArea)

}
