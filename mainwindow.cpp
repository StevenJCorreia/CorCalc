#include "mainwindow.h"
#include "ui_mainwindow.h"

double value = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("CorCalc");

    ui->display->setText(QString::number(value));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; ++i) {
        QString buttonName = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttonName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }
    connect(ui->add, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->subtract, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->multiply, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->divide, SIGNAL(released()), this, SLOT(mathButtonPressed()));
    connect(ui->equal, SIGNAL(released()), this, SLOT(equalButtonPressed()));
    connect(ui->changeSign, SIGNAL(released()), this, SLOT(changeNumberSign()));
    connect(ui->clear, SIGNAL(released()), this, SLOT(clearButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeNumberSign() {
    QString displayValue = ui->display->text();
    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayValue)) {
        double dblDisplayValue = displayValue.toDouble();
        double dblDisplayValueSign = -1 * dblDisplayValue;
        ui->display->setText(QString::number(dblDisplayValueSign));
    }
}

void MainWindow::clearButtonPressed() {
    ui->display->clear();
}

void MainWindow::equalButtonPressed() {
    double result = 0.0;
    QString displayValue = ui->display->text();
    double dblDisplayValue = displayValue.toDouble();
    if (addTrigger || subTrigger || mulTrigger || divTrigger) {
        if (addTrigger) {
            result = value + dblDisplayValue;
        } else if (subTrigger) {
            result = value - dblDisplayValue;
        } else if (mulTrigger) {
            result = value * dblDisplayValue;
        } else if (divTrigger) {
            result = value / dblDisplayValue;
        }
    }
    ui->display->setText(QString::number(result));
}

void MainWindow::mathButtonPressed() {
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayValue = ui->display->text();
    value = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    if (QString::compare(buttonValue, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(buttonValue, "*", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    } else if (QString::compare(buttonValue, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else {
        subTrigger = true;
    }
    ui->display->setText("");
}

void MainWindow::numPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayValue = ui->display->text();
    if ((displayValue.toDouble() == 0) || (displayValue.toDouble() == 0.0)) {
        ui->display->setText(buttonValue);
    } else {
        QString newValue = displayValue + buttonValue;
        double dblNewValue = newValue.toDouble();
        ui->display->setText(QString::number(dblNewValue, 'g', 16));
    }
}
