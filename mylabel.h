#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
//添加鼠标事件头文件
#include <QMouseEvent>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);
protected:
    //实现鼠标释放函数
    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    //自定义一个点击信号
    void clicked();
};

#endif // MYLABEL_H
