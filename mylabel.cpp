#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    //当鼠标按下释放后发送点击信号
    emit clicked();
}
