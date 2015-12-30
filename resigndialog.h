#ifndef RESIGNDIALOG_H
#define RESIGNDIALOG_H

#include <QDialog>

namespace Ui {
class ResignDialog;
}

class ResignDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResignDialog(QWidget *parent = 0);
    ~ResignDialog();

private:
    Ui::ResignDialog *ui;
};

#endif // RESIGNDIALOG_H
