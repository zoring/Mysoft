class NetMsgToShow;

#ifndef PERSONLIST_H
#define PERSONLIST_H
#include "persongrounditem.h"
#include "QListWidget"
#include <QObject>
#include <QVBoxLayout>
#include <iostream>
#include <list>


class PersonList : public QListWidget
{

public:
    explicit PersonList(NetMsgToShow *NetToshow,QListWidget *parent = 0);
    bool StaticMainWindow();
    bool AddGround(std::string GroundName); //增加组
    //bool DelGround(PersonGroundItem Grounds);//删除组
public slots:
    void GetMsg(int number);
private:
    int UserId;
    std::list<PersonGroundItem> Grouds;   // 组容器
    bool StaticList( QVBoxLayout* layout);
    bool StaticGround(std::string keys);
    int  OnChageGround();
    NetMsgToShow *NetToshow;
signals:


};

#endif // PERSONLIST_H
