#ifndef WINSCENE_H
#define WINSCENE_H

#include<QMainWindow>
#include<QPainter>
#include<QPaintDevice>
#include<QPixmap>
#include<QMenu>
#include<QMenuBar>
#include<QLabel>
#include<QAction>
#include<QFont>
#include"mybutton.h"

/*************************************************

类名：WinScene
    胜利界面的实现。

相关函数介绍：
    void paintEvent(QPaintEvent *e)
                          重写绘图事件
    void backtomainscene(QMainWindow*)
                          返回按钮的实现
    void mouseReleaseEvent(QMouseEvent *e)
                          做有第二个参数的按钮弹起特效

**************************************************/

class WinScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit WinScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    void backtomainscene(QMainWindow *);
    MyButton *btn_back;

signals:

};

#endif // WINSCENE_H
