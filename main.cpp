#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include <QTextCodec>
#include "QPushButton"
#include <iostream>
#include "QLabel"
#include "QWidget"
#include "QLayout"
#include "QGridLayout"
#include "QGroupBox"
#include "QListWidget"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "persongrounditem.h"
#include "personlist.h"
#include "wechatcontrol.h"
#include <QMetaType>
#include <QDebug>

#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
      qRegisterMetaType<vector<string> >("vector<string>");
        qRegisterMetaType<string>("string");
        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());//设置编码
        WeChatControl* adf = new WeChatControl();
        QDir dir;

        qDebug() <<  dir.currentPath() << endl;
         return a.exec();

//        if (dlg.exec() == QDialog::Accepted)
//        {
//           w.show();
//
//        }
//        else return 0;
}

