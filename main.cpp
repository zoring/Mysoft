#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        MainWindow w;
        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());//设置编码
        LoginDialog dlg;
        w.show();
        return a.exec();
//        if (dlg.exec() == QDialog::Accepted)
//        {
//           w.show();
//           return a.exec();
//        }
//        else return 0;
}
