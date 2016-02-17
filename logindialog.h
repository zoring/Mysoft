class WeChatControl;
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

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

private:
    Ui::LoginDialog *ui;
    bool CheckUserAndPassword();
    WeChatControl* control;
    bool IsLogin;
};

#endif // LOGINDIALOG_H
