#ifndef LEVEL_H
#define LEVEL_H

#include <QWidget>
#include <QList>
#include <mylabel.h>
#include <QTimer>
#define WIDTH 450
#define HEIGHT 800
namespace Ui {
class Level;
}

class Level : public QWidget
{
    Q_OBJECT

public:
    explicit Level(int levelNum,QWidget *parent = nullptr);
    ~Level();

private:
    Ui::Level *ui;
    struct image{
        QString imagePaht;
        int i;
    };
    struct myLabel{
        MyLabel *lab;
        int num;
        struct image imagePath ;
    };

    int levelNum ;
    int clickedFront = 65535;
    QList<myLabel> labList;
    QTimer *timer;
    //lab标签点击处理
    //参数为被点击的lab的号
    void labClickedLogic(int clickNum);
    void timeOut();
    signals:
     void closeOut();
};

#endif // LEVEL_H
