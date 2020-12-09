#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->count = 0;
    DatabaseConnect();
    DatabaseInit();

    DatabasePopulate();
    //QObject::connect()

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: update(){
    QString text = QString("%1").arg(this->count);
    ui->displayCnt->setText(text);
    DatabasePopulate();
    //record value and time to export to sql database?
}

void MainWindow::DatabaseConnect()
{
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        QTextStream(stdout) << "Driver available" << endl;

        db.setDatabaseName("sqldb3");
        //db.setDatabaseName("sqldb3");

        if(!db.open())
            qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
    }
    else
        qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";
}

void MainWindow::DatabaseInit()
{
    QSqlQuery query("CREATE TABLE readings (id INTEGER PRIMARY KEY, count INTEGER)");
 //QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");
    if(!query.isActive())
        qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();

}

void MainWindow::DatabasePopulate()
{
    QSqlQuery query;
    if(!query.exec("INSERT INTO readings (count) VALUES(1)"))
     //if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
            qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
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
