#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mybutton.h"
#include<QPushButton>
#include<QTimer>
#include <QSound>
#include "choosescene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 系统创建ui界面默认调用
    ui->setupUi(this);

    // 点击退出，退出游戏
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });


    // 重新调整窗口大小并且设置固定大小
    this->resize(500,800);
    this->setFixedSize(500,800);//设定固定大小

    // 设置游戏的标题和图标
    this->setWindowTitle("翻金币");
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置开始按钮音效
    QSound * startbtnsound = new QSound(":/res/TapButtonSound.wav");

    // 开始按钮的制作
    MyButton *startBtn = new MyButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    choose=new ChooseScene;


    playMusic(0);




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


    // 将开始按钮与下一个场景进行绑定转换
    connect(startBtn,&MyButton::clicked,[=](){
    startBtn->zoom();
    startbtnsound->play();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            playMusic(1);
            choose->setGeometry(this->geometry());
            choose->show();
            choose->playMusic(0);
    });

});
    // 点击按钮返回主界面的设置
    choose->backtomain(this);


}

// 重写绘图事件
void MainWindow::paintEvent(QPaintEvent *event)
{
    // 创建一个绘画家对象
    QPainter painter(this);

    // 绘制主场景标题
    QPixmap title;//主场景标题
    title.load(":/res/Title.png");
    painter.drawPixmap(10,30,title);//绘制标题图片

    // 绘制主场景对象，并且按照实际情况进行拉伸
    QPixmap map;
    map.load(":/res/PlayLevelSceneBg.png");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),map);

}

void MainWindow::playMusic(bool isPlaying)
{
    static QSound * background1 = new QSound(":/res/RoyalDays.wav");
    if (isPlaying)
        background1->stop();
    else {
        background1->play();
        background1->setLoops(-1);
        }
}
MainWindow::~MainWindow()
{
    delete ui;
}

