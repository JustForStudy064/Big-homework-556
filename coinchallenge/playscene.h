#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<QFile>
#include<QMainWindow>
#include<QPainter>
#include<QMenu>
#include<QMenuBar>
#include<QAction>
#include<QTimer>
#include<vector>
#include<QLabel>
#include<QString>
#include<QDebug>
#include<QVector>
#include"path.h"
#include"tips.h"
#include<QFont>
#include"coin.h"
#include"winscene.h"
#include"mybutton.h"
#include"sceneconfig.h"
#include<QPen>

/*************************************************
类名：PlayScene
    游戏场景类

相关函数介绍：
    void zoom();            做默认按钮的按下，弹起特效
    void mousePressEvent(QMouseEvent*e)
                          做有第二个参数的按钮按下特效
    void mouseReleaseEvent(QMouseEvent *e)
                          做有第二个参数的按钮弹起特效

**************************************************/

class ChooseScene;

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
   // explicit PlayScene(QWidget *parent = nullptr);
   PlayScene(int index);
   void paintEvent(QPaintEvent*);
   void backtochoose(ChooseScene*);
   void Helpersendtips();

   void godhand();
   void getwindow(ChooseScene *);
   void playMusic(bool);


   bool ifwin;
   bool ifadd;
   int barindex;
   tips *tip;
   WinScene *win;
   SceneConfig config;
   QAction *tipsaction;
   QAction *god;
   path *comparation;
   coin *coinset[4][4];
   MyButton *btn_back;
   QVector<path*>helper;
   QVector<path*>answer;
   bool array[4][4];
   QTimer*counter;
   int time;
   ChooseScene *back;
   void recordscore();
   void getbestrecord();
   int best;
   bool recordempty;


signals:

};

#endif // PLAYSCENE_H
