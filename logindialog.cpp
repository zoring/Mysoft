#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"
#include "wechatcontrol.h"
LoginDialog::LoginDialog(WeChatControl* control,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog) ,
   control(control)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_QuitButton_clicked()
{

}

void LoginDialog::on_LoginButton_clicked()
{
    if (CheckUserAndPassword()){
        IsLogin = true;
         control->IsConnet();
        accept();
       //
    }
    else
    {
        QMessageBox::warning(this, tr("Waring"),
                             tr("user name or password error!"),
                               QMessageBox::Yes);
        ui->UserNameEdit->clear();
       ui->PassWordEdit->clear();
       ui->UserNameEdit->setFocus();
    }
}


bool LoginDialog::CheckUserAndPassword(){

    control->CheckUser( ui->UserNameEdit->text().toStdString(), ui->PassWordEdit->text().toStdString());

    return true;


}

bool LoginDialog::GetIsLogin(){
    return IsLogin;
}
