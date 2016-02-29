#include "resigndialog.h"
#include "ui_resigndialog.h"
#include  <boost/smart_ptr.hpp>
#include <sstream>
#include <iostream>
using namespace std;
ResignDialog::ResignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResignDialog)
{
    ui->setupUi(this);
}

ResignDialog::~ResignDialog()
{
    delete ui;
}

QPushButton* ResignDialog::GetButton(){
    return ui->resigin;
}

string ResignDialog::GetEditeMsg(){
    int UserNameSize = ui->UserNameEdit->text().size() ;
    int PasswordSize = ui->PassWordEdit->text().size() ;
    if ( UserNameSize >= 10 || PasswordSize >= 15 || UserNameSize ==0 || PasswordSize == 0)
        return "";
    string userName = ui->UserNameEdit->text().toStdString();
    string password = ui->PassWordEdit->text().toStdString();
    std::stringstream ss,s2;
    std::string str1,str2;
    ss<<UserNameSize;
    ss>>str1;
    s2<<PasswordSize;
    s2>>str2;
    string msg = "" + str1 +":"+ userName + str2 + ":" + password;
    return msg;
}
