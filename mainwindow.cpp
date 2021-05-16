#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //连接按钮与槽函数
    connect(ui->level1,&QPushButton::clicked,this,[=](){selectLevel(1);});
    connect(ui->level2,&QPushButton::clicked,this,[=](){selectLevel(2);});
    connect(ui->level3,&QPushButton::clicked,this,[=](){selectLevel(3);});
    connect(ui->level4,&QPushButton::clicked,this ,[=](){selectLevel(4);});
}

void MainWindow::selectLevel(int levelNum)
{
    //实例化关卡对象
    level = new Level(levelNum);
    //隐藏当前关卡
    this->hide();
    //显示选中关卡
    level->show();
    connect(level,&Level::closeOut,[=](){
        //获取到关闭信号将上一个页面关闭显示当前页面
        level->close();
        this->show();
    });

}
MainWindow::~MainWindow()
{
    delete ui;
}

