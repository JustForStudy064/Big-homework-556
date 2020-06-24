#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QDebug>
#include"mybutton.h"

#include"winscene.h"
#include"playscene.h"
#include <QSound>
#include <QSoundEffect>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*************************************************
类名：MainWindow
    主窗口类，进入游戏的主场景。

相关函数介绍：
    void paintEvent(QPaintEvent *)
                          重写绘图事件
    void mousePressEvent(QMouseEvent*e)
                          做有第二个参数的按钮按下特效
    void mouseReleaseEvent(QMouseEvent *e)
                          做有第二个参数的按钮弹起特效

**************************************************/

class ChooseScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void playMusic(bool);





    // 创建选择场景界面
    ChooseScene *choose;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


