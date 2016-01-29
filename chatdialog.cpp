#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <string>
#include <qstring.h>
ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{

    ui->setupUi(this);
    ui->ChatEditLog->setReadOnly(true);
    connect(ui->SendMessage,SIGNAL(clicked()),this,SLOT(SendMessage()));

}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::SendMessage(){
    QString sendMsg = ui->WriteMsg->toPlainText();
    string Msg = sendMsg.toStdString();
    ui->WriteMsg->setPlainText("");
}


void ChatDialog::UpdateMessage(string msg){

}
