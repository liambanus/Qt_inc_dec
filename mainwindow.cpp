#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include <QDate>
#include <QDateTime>
#include <QTime>

// to examine db contents in text file navigate to folder and use this command: sqlite3 sqldb3 .dump > database-file.txt

// cd Dropbox/DCU/EmSys\ 513/Qt_inc_dec/build-Qt_inc_dec-Desktop_Qt_5_9_9_GCC_64bit-Debug/

//keyboard mapped to mouse https://www.linuxuprising.com/2019/11/how-to-bind-mouse-buttons-to-keyboard.html


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
    //ui->displayCnt->setText(text);
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
    //check here if db exists and if so change to insert
    QSqlQuery query("CREATE TABLE readings2 (id INTEGER PRIMARY KEY, count INTEGER, Timestamp table_date_time)");
 //QSqlQuery query("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT)");
    if(!query.isActive())
        qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();

}
void MainWindow::DatabasePopulate()
{

   // https://doc.qt.io/qt-5/sql-sqlstatements.html
    QSqlQuery query;
    int cnt = this->count;

    //possible alternative way to escape and insert readings directly:
    //if(!query.exec("INSERT INTO readings (count) VALUES( '"+cnt+"')"))

    //this was the cleanest method of inserting a variable to the database; preparing/binding values
    //https://forum.qt.io/topic/117567/how-to-insert-numbers-in-sqlite-database

    query.prepare("INSERT INTO readings2 (count, Timestamp) VALUES(?,?)");
    //QDateTime timestamp = QDateTime::currentDateTime();
   // timestamp.addDays(1);

    query.addBindValue(cnt);


   //QString curtime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
   QString curtime = QDateTime::currentDateTime().toString("HH:mm:ss");
   // QString QDate::toString(Qt::DateFormat format = Qt::TextDate) const

    query.addBindValue(curtime);

    //QString QTime::toString(QStringView format) const
    //(Timestamp)

   // query.bindValue(":datetime", timestamp);// 2017-09-05T11:50:39
    // Custom format
   // query.bindValue(":datetime", timestamp.toString("yyyy-MM-dd hh:mm:ss"));  // same as above but without the T


   // query.addBindValue("2004-12-11 13:00:00");
   // query.addBindValue(1, "+1 day");
    if(!query.exec())


     //if(!query.exec("INSERT INTO people(name) VALUES('Eddie Guerrero')"))
            qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
}

//need a function for generating time stamp or just use predefs?



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

void MainWindow:: delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_pushButton_3_clicked()
{




    QSqlQuery query;
    query.prepare("SELECT Timestamp FROM readings2 WHERE id = 1");
    //query.addBindValue(mInputText->text().toInt());

    if(!query.exec())
      qWarning() << "ERROR: " << query.lastError().text();



    if(query.first())
      ui->mOutputText->setText(query.value(0).toString());
    else
       ui->mOutputText->setText("person not found");

    //QString text = QString("%1").arg(this->count);
   // ui->displayCnt->setText(text);
    //update();
}
