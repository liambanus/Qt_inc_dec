#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->count = 0;
    //QObject::connect()
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: update(){
    QString text = QString("%1").arg(this->count);
    ui->displayCnt->setText(text);
    //record value and time to export to sql database?
}

void MainWindow::on_pushButton_clicked()
{
    this->count++;
    update();
}


void MainWindow::on_pushButton_2_clicked()
{
    this->count--;
    update();
}
