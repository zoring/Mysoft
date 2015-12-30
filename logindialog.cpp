#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
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
    if (ui->UserNameEdit->text() == tr("123") && ui->PassWordEdit->text() == tr("123")){
        accept();
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
