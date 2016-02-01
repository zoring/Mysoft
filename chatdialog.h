class NetMsgToShow;

#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include <QDialog>
#include <string>

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
    explicit ChatDialog(NetMsgToShow* sendObj, QWidget *parent = 0);
    ~ChatDialog();

     void UpdateMessage(string msg);

private:
    Ui::ChatDialog *ui;
    NetMsgToShow *SendToNetObj;
private slots:
    void SendMessage();

    //void SendMsg(QString value);

};

#endif // CHATDIALOG_H
