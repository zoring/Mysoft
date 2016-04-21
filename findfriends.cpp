#include "findfriends.h"
#include "ui_findfriends.h"

FindFriends::FindFriends(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindFriends)
{
    ui->setupUi(this);
}

FindFriends::~FindFriends()
{
    delete ui;
}
