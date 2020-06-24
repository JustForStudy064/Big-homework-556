#include "winscene.h"
#include<QPainter>
#include <QSound>
#include "choosescene.h"
WinScene::WinScene(int t,int u,int v,bool a,bool b)
{      //先实现菜单栏
       this->resize(500,800);
       QMenuBar*bar=menuBar();
       this->setMenuBar(bar);
       QMenu*startmenu=new QMenu("start");
       bar->addMenu(startmenu);
       QAction*quitaction=new QAction("exit");
       startmenu->addAction(quitaction);
       connect(quitaction,&QAction::triggered,[=](){
           this->close();
       });
       QLabel*label=new QLabel(this);
       QFont font;
       font.setFamily("华文新魏");
       font.setPointSize(30);
       label->setFont(font);
       label->setGeometry(150,300,400,40);
       label->setText("游戏胜利");


       best=u;
       breakrecord=a;
       empty=b;
       index=v;

       btn_back=new MyButton(":/res/BackButton.png");
       btn_back->setParent(this);
       btn_back->move(this->width()-btn_back->width(),this->height()-btn_back->height());

       timeplay=t;
}
void WinScene::paintEvent(QPaintEvent*e)
{

    QPainter painter(this);
    QPixmap map;//主场景对象
    QPixmap title;//主场景标题
    title.load(":/res/Title.png");
    map.load(":/res/PlayLevelSceneBg.png");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),map);//绘制图片，并且按照实际情况进行拉伸
    painter.drawPixmap(10,30,title);//绘制标题图片
    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::white);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(30);
    painter.setFont(font);
    painter.setPen(pen);
    int minute=timeplay/60;
    int second=timeplay%60;
    QString minuteshow;
    QString secondshow;
    if(minute<10)
    {
        minuteshow=QString("0%1").arg(minute);
    }
    else
    {
        minuteshow=QString("%1").arg(minute);
    }
    if(second<10)
    {
        secondshow=QString("0%1").arg(second);
    }
    else
    {
        secondshow=QString("%1").arg(second);

    }

    QString timeshow=QString("用时:")+minuteshow+QString(":")+secondshow;
    painter.drawText(120,250,timeshow);

    int minute1=best/60;
    int second1=best%60;
    QString minuteshow1;
    QString secondshow1;
    if(minute1<10)
    {
        minuteshow1=QString("0%1").arg(minute1);
    }
    else
    {
        minuteshow1=QString("%1").arg(minute1);
    }
    if(second1<10)
    {
        secondshow1=QString("0%1").arg(second1);
    }
    else
    {
        secondshow1=QString("%1").arg(second1);

    }
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    QString timeshow1=minuteshow1+QString(":")+secondshow1;

    if(empty)
    {
        painter.drawText(70,400,"当前无任何记录");
    }
    else if(breakrecord&&!empty)
    {

        painter.drawText(70,400,"恭喜你打破记录");
        painter.drawText(180,450,"原纪录:");
        painter.drawText(190,500,timeshow1);
    }
    else if(!breakrecord&&!empty)
    {
        painter.drawText(180,400,"原纪录:");
        painter.drawText(190,450,timeshow1);
    }
    pen.setColor(Qt::white);
    font.setPointSize(40);
    painter.setFont(font);
    painter.setPen(pen);
    painter.drawText(165,200,QString("第%1关").arg(index));


}
void WinScene::backtomainscene(ChooseScene *a)
{
    connect(btn_back,&MyButton::clicked,[=](){
        btn_back->zoom();
        QSound * backbtnsound3 = new QSound(":/res/BackButtonSound.wav");
        backbtnsound3->play();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            a->playMusic(0);
            a->show();
        });
    });
}

