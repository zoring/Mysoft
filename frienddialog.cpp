#include "frienddialog.h"
#include "ui_frienddialog.h"

FriendDialog::FriendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendDialog)
{
    ui->setupUi(this);
}

FriendDialog::~FriendDialog()
{
    delete ui;
}
