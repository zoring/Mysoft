#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <string>
#include "persongrounditem.h"
#include <qstring.h>
#include "netmsgtoshow.h"
#include <boost/bind.hpp>
#include <iostream>
ChatDialog::ChatDialog(NetMsgToShow* sendObj,PersonGroundItem* persondata, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog),persondata(persondata),
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
  SendToNetObj->SendMsg(persondata->GetUserId(),Msg);
    //boost::bind(&NetMsgToShow::SendMsg,SendToNetObj, 123,Msg);
    ui->WriteMsg->setPlainText("");
    ui->ChatEditLog->insertPlainText(sendMsg);
}


void ChatDialog::UpdateMessage(){
    vector<string > Hasread = persondata->PopNotReadMsg();
    for (vector<string>::iterator iter = Hasread.begin(); iter != Hasread.end() ;++iter)
    {QString Update = QString::fromStdString(*iter);
     ui->ChatEditLog->insertPlainText(Update);
    }
    Hasread.clear();
}
