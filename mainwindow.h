#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    //void on_displayCnt_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void update();

    int count, time, patience;

    void DatabaseConnect();
        void DatabaseInit();
        void DatabasePopulate();
};
#endif // MAINWINDOW_H
