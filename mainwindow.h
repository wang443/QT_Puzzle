#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <level.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //关卡挑战
    void selectLevel(int levelNum);
    //创建关卡对象
    Level *level = nullptr;
};
#endif // MAINWINDOW_H
