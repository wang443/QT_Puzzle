#include "level.h"
#include "ui_level.h"
#include <QDebug>
#include <QPixmap>
#include <QtCore>
#include <QtGlobal>
#include <QRandomGenerator>
Level::Level(int levelNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level)
{
    ui->setupUi(this);
    qDebug()<<"当前选择第"<<levelNum<<"关";
    this->levelNum = levelNum;
    //判断每一个label的宽高
    int labelWidth = WIDTH / (levelNum +1);
    int labelHeight = HEIGHT / (levelNum +1);

    //导入图片路径
     for(int i=1;i<=(levelNum+1)*(levelNum+1);i++)
     {
        QString path = QString(":/res/leve%1/cat_%2.png").arg(levelNum).arg(i, 2, 10, QChar('0'));
        struct myLabel mylabel;
        struct image imagePath;
        imagePath.i = i-1;
        imagePath.imagePaht  = path;
        mylabel.imagePath = imagePath;
        labList.append(mylabel);
    }

     //利用随机数打乱图片
     for(int i=0;i<(levelNum+1)*(levelNum+1);i++)
     {
         //获取随机数 //随机数产生范围为当前lab总数
        int count = QRandomGenerator::global()->bounded((levelNum+1)*(levelNum+1));
        //交换随机数与当前i对应的图片
        struct image image1 = labList.at(count).imagePath;
        struct image image2 = labList.at(i).imagePath;
        labList[count].imagePath = image2;
        labList[i].imagePath = image1;
     }
    //利用循环创建label
    for(int i=0;i<(levelNum+1)*(levelNum+1);i++)
    {
        //创建lab对象
        MyLabel *lab = new MyLabel(this);
        labList[i].lab = lab;
        labList[i].num = i;
        //显示显示图片
            //创建图片对象
        QPixmap image;
            //加载图片路径
        image.load(labList.at(i).imagePath.imagePaht);
        image = image.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio);
        //标签显示图片
        lab->setPixmap(image);
        //标签适应图片
        lab->setScaledContents(true);
        //重置lab大小
        lab->resize(labelWidth,labelHeight);
        //移动Lab到指定位置
        lab->move(i%(levelNum+1)*labelWidth,i/(levelNum+1)*labelHeight);
        //判断是否被点击
        connect(lab,&MyLabel::clicked,this,[=](){labClickedLogic(i);});
    }

    //利用QTimer判断是否正确
    timer = new QTimer(this);
    //每100ms进行一次判断
    timer->start(100);
    connect(timer,&QTimer::timeout,this,&Level::timeOut);
}
void Level::timeOut()
{
    //循环判断图片的num与lab的num是否相等
    int count  = 0;
   for(int i=0;i<(levelNum+1)*(levelNum+1);i++)
   {
       int image_num = labList.at(i).imagePath.i;
       int lab_num = labList.at(i).num;
       //如果不相等则退出循环
       if(image_num != lab_num)
       {
           break;
       }
       else
       {
           //相等将i赋值给count
           count = i;

       }
   }
   //当count 等于(levelNum+1)*(levelNum+1)-1时表示所有的都相等//for未<号循环未达到(levelNum+1)*(levelNum+1)
   if(count == (levelNum+1)*(levelNum+1)-1)
   {
       qDebug()<<"成功";
       timer->stop();
       //显示成操作
        MyLabel *lab = new MyLabel();
        lab->resize(WIDTH,HEIGHT);
        QPixmap pix;
        pix.load(":/res/success.jpg");
         pix = pix.scaled(WIDTH / (levelNum +1), HEIGHT / (levelNum +1), Qt::KeepAspectRatio);
        lab->setPixmap(pix);
        this->hide();
        lab->show();
        connect(lab,&MyLabel::clicked,[=](){
            //关闭
            lab->close();
            //发送退出信号
            emit closeOut();
        });
   }
}
void Level::labClickedLogic(int clickNum)
{
    if(clickedFront == 65535)
    {
        //没有被点击标签
        //记录当前标签
       clickedFront =  clickNum;
    }
    else
    {


        //前面有标签被点击
        //获取被点击lab标签的地址与显示数字
        MyLabel *lab1 = labList.at(clickedFront).lab;
        QString imagePath1 = labList.at(clickedFront).imagePath.imagePaht;
        //获取当前lab标签的地址与显示数字
        MyLabel *lab2 = labList.at(clickNum).lab;
        QString imagePath2 = labList.at(clickNum).imagePath.imagePaht;
        //交换显示图片
        QPixmap image;
        image.load(imagePath1);
         image = image.scaled(WIDTH / (levelNum +1), HEIGHT / (levelNum +1), Qt::KeepAspectRatio);
         lab2->setPixmap(image);
         image.load(imagePath2);
          image = image.scaled(WIDTH / (levelNum +1), HEIGHT / (levelNum +1), Qt::KeepAspectRatio);
        lab1->setPixmap(image);
        //交换结构体中的数字
        struct image image1 = labList.at(clickedFront).imagePath;
        struct image image2 = labList.at(clickNum).imagePath;
        labList[clickedFront].imagePath = image2;
        labList[clickNum].imagePath = image1;
        //将点击数字重置
        clickedFront = 65535;
    }
}
Level::~Level()
{
    delete ui;
}
