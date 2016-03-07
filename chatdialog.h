class NetMsgToShow;
class PersonGroundItem;
#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include <QDialog>
#include <string>
#include <map>
namespace Ui {
class ChatDialog;
}
using namespace std;
class ChatDialog : public QDialog
{
    Q_OBJECT

signals:
    void dlgReturn(QString);
public:
    explicit ChatDialog(NetMsgToShow* sendObj,PersonGroundItem* persondata, QWidget *parent = 0);
    ~ChatDialog();

     void UpdateMessage();

private:
    Ui::ChatDialog *ui;
    NetMsgToShow *SendToNetObj;
    PersonGroundItem* persondata;

private slots:
    void SendMessage();

    //void SendMsg(QString value);

};

#endif // CHATDIALOG_H
