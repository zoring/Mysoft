#ifndef GROUNDMSG_H
#define GROUNDMSG_H
#include <string>
#include <QWidget>
#include <vector>
#include "persongrounditem.h"
using namespace std;
class GroundMsg : public QListWidget
{
    Q_OBJECT
public:
    explicit GroundMsg(const string GroundName,const int GroundId,QListWidget  *parent = 0);
    void AddGroundMember(const int GroundMemberId,PersonGroundItem* GroundMembers);
    bool DeleteGroundMember(const int GroundMemberId);
    void OpendOrCloseGround();
    void ReviceMegFromNet(int userId, string Meg,string UserName);
    bool IsOpen();

signals:

public slots:

private:
    void InsertGroundMember(PersonGroundItem* GroundMembers);
    int Count;
    bool Open;
   const string GroundName;
   const int GroundId;
   map<int,PersonGroundItem*>    GroundMember;
};

#endif // GROUNDMSG_H
