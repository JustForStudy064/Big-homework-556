#include "choosescene.h"
#include<QPainter>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include"mybutton.h"
#include<QTimer>
#include<vector>
#include<QLabel>
#include<QString>
#include<QDebug>
#include <QSound>
#include "mainwindow.h"
#include "playscene.h"
#include "winscene.h"


ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{
    // 重新调整窗口大小并且设置固定大小
    this->resize(500,800);
    this->setFixedSize(500,800);

    // 设置标题以及标题的图标
    this->setWindowTitle("选择关卡");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));


    // 设置菜单项，并且设置工具栏
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    QMenu*startmenu=new QMenu("开始");
    bar->addMenu(startmenu);
    QAction*quitaction=new QAction("退出");
    startmenu->addAction(quitaction);

    // 完成退出功能的实现
    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });

    btn_back=new MyButton(":/res/BackButtonSelected.png");//创建返回按钮
    btn_back->setParent(this);
    btn_back->move(350,600);


    //静音按钮1
    MyButton * mutebutton1 = new MyButton(":/res/NoMute1.png");
    mutebutton1->setParent(this);
    mutebutton1->move(this->width() - mutebutton1->width(), this->height() - mutebutton1->height());

    //静音按钮2
    MyButton * mutebutton2 = new MyButton(":/res/Mute1.png");
    mutebutton2->setParent(this);
    mutebutton2->move(this->width() - mutebutton2->width(), this->height() - mutebutton2->height());
    mutebutton2->hide();
    mutebutton2->setAttribute(Qt::WA_TransparentForMouseEvents, true);


    connect(mutebutton1, &MyButton::clicked, [=](){
       mutebutton1->hide();
       mutebutton2->show();
       playMusic(1);
       mutebutton2->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    });

    connect(mutebutton2, &MyButton::clicked, [=](){
        mutebutton2->hide();
        mutebutton1->show();
        playMusic(0);
        mutebutton2->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    });

    playscene=NULL;
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
            barchoose.push_back(new MyButton(":/res/LevelIcon.png"));
            barchoose[4*i+j]->setParent(this);
            barchoose[4*i+j]->move((j+1)*90,(i+1)*120);

            connect(barchoose[4*i+j],&MyButton::clicked,[=](){
                barchoose[4*i+j]->zoom();
                QSound * choosesound = new QSound(":/res/TapButtonSound.wav");
                choosesound->play();
                QTimer::singleShot(200,this,[=](){
                    qDebug()<<"you choose"<<4*i+j+1<<"bar";
                    playscene=new PlayScene(4*i+j+1);
                    this->hide();
                    playMusic(1);
                    playscene->setGeometry(this->geometry());
                    playscene->playMusic(0);
                    playscene->show();
                    playscene->backtochoose(this);
                    playscene->getwindow(this);
                });
            });


            QLabel*label=new QLabel(this);
            label->setFixedSize(barchoose[4*i+j]->width(),barchoose[4*i+j]->height());
            label->setText(QString::number(4*i+j+1));
            label->move((j+1)*90,(i+1)*120);
            label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);//设计鼠标穿透，因为button在label的下面

        }
    }


}

void ChooseScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap map;//主场景对象
    QPixmap title;//主场景标题
    title.load(":/res/Title.png");
    map.load(":/res/PlayLevelSceneBg.png");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),map);//绘制图片，并且按照实际情况进行拉伸
    painter.drawPixmap(10,30,title);//绘制标题图片
}


void ChooseScene::backtomain(MainWindow * a)
{
    QSound * backbtnsound = new QSound(":/res/BackButtonSound.wav");
    //点击按钮后返回主窗口
    connect(btn_back,&MyButton::clicked,[=](){
        btn_back->zoom();
        backbtnsound->play();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            playMusic(1);
            a->playMusic(0);
            a->setGeometry(this->geometry());
            a->show();

        });

    });
}

void ChooseScene::playMusic(bool isplaying)
{
     static QSound * background2 = new QSound(":/res/RoyalDays1.wav");
     if (isplaying)
         background2->stop();
     else {
         background2->play();
         background2->setLoops(-1);
    }
}