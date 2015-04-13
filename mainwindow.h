#pragma once

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbFrom_clicked();
    void setText_leFrom(const QString &file);   //源目标得到选择
    void on_pbTo_clicked();
    void textChanged(void);                     //lineEdit内容发生变化
    void on_pbParameterJ_clicked();
    void on_pbParameterD_clicked();
    void on_pbParameterH_clicked();
    void on_actionAboutQt_triggered();
    void on_actionAbout_triggered();

private:
    bool verificationPermission(void);      //检测用户是否拥有mklink所需的高权限或可以提升权限（/D参数需要）
    void runMklink(QStringList arguments);  //运行mklink
    Ui::MainWindow *ui;
    QSqlDatabase *db;       //数据库链接
    bool userHasOrElevatedPermission;   //用户是否拥有mklink所需的高权限或可以提升权限（/D参数需要）
    bool runtimeVerificationPermission; //是否实时检测用户权限
};

