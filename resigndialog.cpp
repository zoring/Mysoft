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

string ResignDialog::GetUserNameEdit(){
    int UserNameSize = ui->UserNameEdit->text().size() ;

    if ( UserNameSize >= 10 ||  UserNameSize ==0  )
        return "";
   return ui->UserNameEdit->text().toStdString();

}

string ResignDialog::GetUserPasswordEdit(){
    int PasswordSize = ui->PassWordEdit->text().size() ;
    if (PasswordSize >= 15 || PasswordSize == 0 )
        return "" ;
    return ui->PassWordEdit->text().toStdString();
}

void ResignDialog::ResetMeg(){
   ui->UserNameEdit->clear();
   ui->PassWordEdit->clear();
   ui->UserNameEdit->setFocus();
}

void ResignDialog::GetResightResult(bool Result){
    if ( Result )
    {
        this->close() ;

    }
    else
       ResetMeg();
}
