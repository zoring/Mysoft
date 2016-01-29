#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <string>
using namespace std;
namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

signals:
    void dlgReturn(QString);
public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();

     void UpdateMessage(string msg);

private:

    Ui::ChatDialog *ui;
private slots:
    void SendMessage();
    //void SendMsg(QString value);

};

#endif // CHATDIALOG_H
