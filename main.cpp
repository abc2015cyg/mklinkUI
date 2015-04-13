#include <QApplication>
#include <QMessageBox>
#include <QSysInfo>

#include "mainwindow.h"

//!对当前系统进行检测，是否满足mklink运行环境
bool systeEvnDetection();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!systeEvnDetection())
    {
        if(QMessageBox::No ==
           QMessageBox::question(0,QObject::tr("系统版本检测"),
                                   QObject::tr("当前系统版本可能不被支持，是否继续"))) {
            return 0;
        }
    }
    MainWindow w;
    w.show();

    return a.exec();
}

bool systeEvnDetection()
{
    switch(QSysInfo::windowsVersion())
    {
        //等待加入win10支持
//        case QSysInfo::WV_WINDOWS10 :
        case QSysInfo::WV_WINDOWS8_1 :
        case QSysInfo::WV_WINDOWS8 :
        case QSysInfo::WV_WINDOWS7 :
        case QSysInfo::WV_VISTA : {
            return true;
        }break;
        default : {
            return false;
        }break;
    }
}
