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
   GroundList->show();

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
ui->centralWidget->show();
this->show();
 return true ;
}


//获取组信息
bool MainWindow::StaticList( QVBoxLayout* layout){

     layout->addWidget(GroundList);
     for (int i =0; i<=1;i++)
     {
          QListWidgetItem* v= new QListWidgetItem();
         v->setSizeHint(QSize(100,120));

         GroundList->insertItem(i,v);

  //  PersonGroundItem*  test = new PersonGroundItem(i,"fd","erf");

 //  GroundList->setItemWidget(v,test);

//test->show();
GroundList->show();

//    QWidget *mw = new QWidget();
//    QPalette palette = mw->palette();
//    palette.setBrush(mw->backgroundRole(), QBrush(QPixmap("/home/zoring/test/1.png")));
//    mw->setPalette(palette);


//  ///  layout->addWidget(PersonImage);


////    mw->setPalette(palette);
//    mw->resize(40, 40);
//    mw->setAutoFillBackground(true);

//    //mw->setWindowFlags(Qt::FramelessWindowHint);
//    mw->show();

   // QObject::connect(test,&QPushButton::clicked,this,StaticGround);
     }
    



     return true;

}

//获取好友列表信息
bool MainWindow::StaticGround(string keys){


    return true;

}

//添加新的组
bool MainWindow::AddGround(string GroundName){
    QString QGroundName = QString(QString::fromLocal8Bit(GroundName.c_str()));



}

bool MainWindow::DelGround(PersonGroundItem Grounds){
   Grouds.remove(Grounds);

}

