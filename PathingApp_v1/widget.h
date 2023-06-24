#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <iostream>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QPushButton *button = new QPushButton("Start");


public slots:
    void buttonClicked();

private:
    QGroupBox *createOptionsGroup();
    QGroupBox *createInputGroup();
    QPlainTextEdit *textAreaDraw();
    QPlainTextEdit *termianlArea();
    QPlainTextEdit *textArea = new QPlainTextEdit();
    QTextEdit *textz = new QTextEdit();
    QTextEdit *textd = new QTextEdit();

};




#endif // WIDGET_H
