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



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());//设置编码
        LoginDialog dlg;
        PersonList* ad = new PersonList();
        ad->show();
         return a.exec();

//        if (dlg.exec() == QDialog::Accepted)
//        {
//           w.show();
//
//        }
//        else return 0;
}

