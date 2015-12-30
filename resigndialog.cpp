#include "resigndialog.h"
#include "ui_resigndialog.h"

ResignDialog::ResignDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResignDialog)
{
    ui->setupUi(this);
}

ResignDialog::~ResignDialog()
{
    delete ui;
}
