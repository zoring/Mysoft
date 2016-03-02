#ifndef RESIGNDIALOG_H
#define RESIGNDIALOG_H

#include <QDialog>
#include <string>
namespace Ui {
class ResignDialog;
}
using namespace std;
class ResignDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResignDialog(QWidget *parent = 0);
    ~ResignDialog();

    QPushButton* GetButton();
    string GetUserNameEdit();
    string GetUserPasswordEdit();
    void GetResightResult(bool Result);

private:
    Ui::ResignDialog *ui;
      void ResetMeg();

};

#endif // RESIGNDIALOG_H
