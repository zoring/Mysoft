#include "mainwindow.h"
#include "ui_mainwindow.h"
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

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   StaticMainWindow();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化聊天界面
bool MainWindow::StaticMainWindow(){

 QHBoxLayout* Hlayout = new QHBoxLayout();
 QVBoxLayout* layout = new QVBoxLayout();
  QVBoxLayout* StaticLists = new QVBoxLayout();
QPushButton* FriendButton = new QPushButton("Friend");
QPushButton* GroundButton = new QPushButton("Ground");
Hlayout->addWidget(FriendButton);

Hlayout->addWidget(GroundButton);
StaticList(StaticLists);
 layout->addItem(Hlayout);
 layout->addItem(StaticLists);
ui->centralWidget->setLayout(layout);
 return true ;
}


//获取组信息
bool MainWindow::StaticList( QVBoxLayout* layout){





     for (int i =0; i<=10;i++)
     {
    PersonGroundItem*  test = new PersonGroundItem("friends",GroundList);

   // QObject::connect(test,&QPushButton::clicked,this,StaticGround);
     }
     new PersonGroundItem("tefdst",GroundList);
     layout->addWidget(GroundList);
     return true;

}

//获取好友列表信息
bool MainWindow::StaticGround(string keys){

    for (std::list<PersonGroundItem>::iterator iter = Grouds.begin(); iter != Grouds.end(); ++iter) {
         if(!(*iter).getIsHidden())
         {
              return true ;
         }
    }
    return true;

}

//添加新的组
bool MainWindow::AddGround(string GroundName){
    QString QGroundName = QString(QString::fromLocal8Bit(GroundName.c_str()));
     PersonGroundItem*  NewGround = new PersonGroundItem(QGroundName,GroundList);
     Grouds.push_back(*NewGround);


}

bool MainWindow::DelGround(PersonGroundItem Grounds){
   Grouds.remove(Grounds);

}

