//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H
//#include <QDebug>
#pragma once

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    //void on_displayCnt_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void update();

    int count, time, patience;

   /*For SQLite the only configuration needed is the database name. We can set that with setDatabaseName.

It’s important to notice that “:memory:” is a special name for SQLite. It will create a temporary database existing entirely in memory until the connection is closed. In case you wanted to create a permanent SQLite database on disk, you have to pass a full file path to setDatabaseName.
 */
    void DatabaseConnect();
        void DatabaseInit();
        void DatabasePopulate();
};
//#endif // MAINWINDOW_H
