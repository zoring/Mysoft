class WeChatControl;
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "resigndialog.h"
#include <QDialog>
#include <string>
using namespace std;
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(WeChatControl* control,QWidget *parent = 0 );
    ~LoginDialog();
    bool GetIsLogin();
private slots:
    void on_QuitButton_clicked();

    void on_LoginButton_clicked();
    void on_SightButton_clicked();
    void on_GetSightUpMsg();
private:
    Ui::LoginDialog *ui;
    bool CheckUserAndPassword();
    WeChatControl* control;
    bool IsLogin;
    ResignDialog* SightUpDialog;
};

#endif // LOGINDIALOG_H
