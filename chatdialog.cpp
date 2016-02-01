#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <string>
#include <qstring.h>
#include "netmsgtoshow.h"
#include <boost/bind.hpp>
#include <iostream>
ChatDialog::ChatDialog(NetMsgToShow* sendObj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog),
    SendToNetObj(sendObj)
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
  SendToNetObj->SendMsg(123,Msg);
    //boost::bind(&NetMsgToShow::SendMsg,SendToNetObj, 123,Msg);
    std::cout<<Msg<<std::endl;
    ui->WriteMsg->setPlainText("");
}


void ChatDialog::UpdateMessage(string msg){

}
