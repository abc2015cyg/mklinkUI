#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "mainwindow.h"
#include "myfiledialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    db(new QSqlDatabase()),
    userHasOrElevatedPermission(false),
    runtimeVerificationPermission(false)
{
    ui->setupUi(this);

    db->open("link.db","QSQLite");
    userHasOrElevatedPermission = verificationPermission();

    connect(ui->leFrom, SIGNAL(textChanged(const QString &)),
            this,       SLOT(textChanged()) );
    connect(ui->leTo,   SIGNAL(textChanged(const QString &)),
            this,       SLOT(textChanged()) );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

//!获取源目标
//!  note:由于QFileDialog::exec()对话框为系统对话框，无法修改
//!       使用QFileDialog::show()不是模态
void MainWindow::on_pbFrom_clicked()
{
    MyFileDialog *a = new MyFileDialog(this);
    a->setAttribute(Qt::WA_DeleteOnClose, true);
    a->show();
    connect(a,      SIGNAL  (fileSelected(const QString &)),
            this,   SLOT    (setText_leFrom(const QString &)));
}

void MainWindow::setText_leFrom(const QString &file)
{
    ui->leFrom->setText(QString(file).replace("/","\\"));
}

void MainWindow::on_pbTo_clicked()
{
    ui->leTo->setText(QFileDialog::getSaveFileUrl().toString()
                      .trimmed().mid(QString("file:///").size()).replace("/","\\"));
}

//!根据输入的是文件或文件夹来启用选项
void MainWindow::textChanged(void)
{
    //输入不全禁用全部选项
    QString textFrom = ui->leFrom->text().trimmed();
    QString textTo = ui->leTo->text().trimmed();
    if(textFrom.isEmpty() || textTo.isEmpty() )
    {
        ui->pbParameterD->setEnabled(false);
        ui->pbParameterJ->setEnabled(false);
        ui->pbParameterH->setEnabled(false);
        return;
    }

    if(runtimeVerificationPermission) {
        userHasOrElevatedPermission = verificationPermission();
    }
    QFileInfo file(textFrom);
    if(file.isFile())
    {
        ui->pbParameterD->setEnabled(false);
        ui->pbParameterJ->setEnabled(false);
        ui->pbParameterH->setEnabled(true);
    }
    else if(file.isDir())
    {
        ui->pbParameterJ->setEnabled(true);
        ui->pbParameterH->setEnabled(false);
        //“/D”参数不可以跨盘符
        if(QDir(textTo).root().path() == QDir(textFrom).root().path()) {
            ui->pbParameterD->setEnabled(userHasOrElevatedPermission);
        }
        else {
            ui->pbParameterD->setEnabled(false);
        }
    }
    else
    {
        ui->pbParameterD->setEnabled(false);
        ui->pbParameterJ->setEnabled(false);
        ui->pbParameterH->setEnabled(false);
    }
}

//!检测用户是否拥有mklink所需的高权限或可以提升权限（/D参数需要）
bool MainWindow::verificationPermission()
{
    return false;
}

//!运行mklink
void MainWindow::runMklink(QStringList arguments)
{
    if(QMessageBox::question(this,tr("确认"),"mklink "+arguments.join(" "))
            == QMessageBox::Yes)
    {
        QProcess process(this);
        process.start("cmd.exe",QStringList()<<QString("/C")<<QString("mklink")<<arguments);
        process.waitForStarted();
        process.waitForFinished();
        //显示输出信息
        QByteArray output = process.readAllStandardOutput();
        if(!output.isEmpty()) {
            QMessageBox::information(this,tr("mklink"),QString::fromLocal8Bit(output));
        }
        //显示错误信息
        QByteArray error = process.readAllStandardError();
        if(!error.isEmpty()) {
            QMessageBox::information(this,tr("mklink"),QString::fromLocal8Bit(error));
            //在error中出现\0时可能会转换QString错误
//            const int size = error.size()/sizeof(wchar_t);
//            wchar_t *t = new wchar_t[size+1];               //+1为了添加'\0'
//            wcsncpy(t,(const wchar_t*)error.data(),size);
//            t[size] = '\0';                                 //最后一位'\0'
//            QMessageBox::critical(this,tr("错误"),QString::fromWCharArray(t));
        }
    }
}

void MainWindow::on_pbParameterJ_clicked()
{
    runMklink(QStringList()<<"/J"
              <<ui->leTo->text().trimmed()<<ui->leFrom->text().trimmed());
}

void MainWindow::on_pbParameterD_clicked()
{
    runMklink(QStringList()<<"/D"
              <<ui->leTo->text().trimmed()<<ui->leFrom->text().trimmed());
}

void MainWindow::on_pbParameterH_clicked()
{
    runMklink(QStringList()<<"/H"
              <<ui->leTo->text().trimmed()<<ui->leFrom->text().trimmed());
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr("关于"),QString("<a href = www.github.com/abc2015cyg/mklinkui>源代码</a>"));
}
