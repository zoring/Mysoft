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
    string GetEditeMsg();
private:
    Ui::ResignDialog *ui;

};

#endif // RESIGNDIALOG_H
