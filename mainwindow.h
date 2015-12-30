#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QListWidget>
#include <iostream>
#include <list>
#include "persongrounditem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool StaticMainWindow();
    bool AddGround(std::string GroundName); //增加组
    bool DelGround(PersonGroundItem Grounds);//删除组

private:
    Ui::MainWindow *ui;
    int groundId;
    QListWidget*  GroundList = new QListWidget();
    std::list<PersonGroundItem> Grouds;   // 组容器
    bool StaticList( QVBoxLayout* layout);
    bool StaticGround(std::string keys);
    int  OnChageGround();

};

#endif // MAINWINDOW_H
