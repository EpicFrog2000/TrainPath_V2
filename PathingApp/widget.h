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
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <QComboBox>
#include <QSpinBox>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
;

public slots:
    void buttonClicked();

private:
    QGroupBox *createOptionsGroup();
    QGroupBox *createInputGroup();
    QPlainTextEdit *termianlArea();
    QPlainTextEdit *textArea;
    QVBoxLayout *vbox;
    QComboBox *start;
    QComboBox *end;
    QSpinBox *spin;

signals:
    void wheelEventReceived(QWheelEvent *event);
};

#endif // WIDGET_H
