#include "playscene.h"

PlayScene::PlayScene(int index)
{
    ifadd=true;
    ifwin=false;
    tip=NULL;
    comparation=NULL;
    this->resize(500,800);
    this->setFixedSize(500,800);//设定固定大小
    this->setWindowTitle(QString("游戏关卡%1").arg(index));//设置标题
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));//设置标题的图标

    QMenuBar*bar=menuBar();//设置工具栏
    this->setMenuBar(bar);
    QMenu*startmenu=new QMenu("start");
    bar->addMenu(startmenu);
    QAction*quitaction=new QAction("quit");
    tipsaction=new QAction("tips");
    god=new QAction("god's hand");
    Helpersendtips();

    connect(quitaction,&QAction::triggered,[=](){
        this->close();
    });


    startmenu->addAction(quitaction);
    startmenu->addAction(tipsaction);
    startmenu->addAction(god);
    this->godhand();
    win=new winscene();//创建胜利情景


    btn_back=new MyButton(":/res/BackButtonSelected.png");//创建返回按钮
    btn_back->setParent(this);
    btn_back->move(350,600);

    QLabel*label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setGeometry(30,this->height()-50,120,50);
    label->setText(QString("Level:%1").arg(index));//设置底下那个L



    bool array2[4][4]={{0,1,1,0},{1,0,1,0},{0,0,0,0},{0,1,0,0}};
    answer.push_back(new path(1,1));
    answer.push_back(new path(2,2));
    answer.push_back(new path(4,3));
    answer.push_back(new path(4,1));
    answer.push_back(new path(2,4));
    //答案的路径

    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;j++)
        {
            array[i][j]=array2[i][j];
        }
    }

    //创建金币的图片背景+创建金币
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           QLabel * bg=new QLabel(this);
           QPixmap pix;
           pix.load(":/res/BoardNode.png");
           bg->setGeometry(150+i*50,200+j*50,pix.width(),pix.height());
           bg->setPixmap(pix);;

           coin*little=new coin(array[i][j],i+1,j+1);
           little->setParent(this);
           little->move(152+i*50,202+j*50);
           coinset[i][j]=little;
           connect(little,&coin::clicked,[=](){
           little->changeFlag();
           array[i][j]=!(array[i][j]);
           if(comparation!=NULL)
           {if(comparation->x!=i+1||comparation->y!=j+1)
           {
               ifadd=true;
           }//看看是不是按照按照提示走的
           }
           if(ifadd)
          {
           helper.push_back(new path(i+1,j+1));//把玩家的路径压入向量

          }

           QTimer::singleShot(100,this,[=](){
               if(coinset[i][j]->posx+1<=4)
               {
                   coinset[i+1][j]->changeFlag();
                   array[i+1][j]=!(array[i+1][j]);
               }//检测右边是否有硬币需要翻转
               if(coinset[i][j]->posx-1>=1)
               {
                   coinset[i-1][j]->changeFlag();
                    array[i-1][j]=!(array[i-1][j]);
               }//检测左边是否有硬币需要翻转
               if(coinset[i][j]->posy+1<=4)
               {
                   coinset[i][j+1]->changeFlag();
                    array[i][j+1]=!(array[i][j+1]);
               }//检测下边硬币是否需要反转
               if(coinset[i][j]->posy-1>=1)
               {
                   coinset[i][j-1]->changeFlag();
                   array[i][j-1]=!(array[i][j-1]);
               }//检测上边硬币是否需要反转

               ifwin=true;

               for(int a=0;a<4;++a)
               {
                   for(int b=0;b<4;++b)
                   {
                       if(coinset[a][b]->flag==false)
                       {
                           ifwin=false;
                           break;
                       }
                   }
               }
               QTimer::singleShot(500,this,[=](){
                   if(ifwin)
               {
                  this->hide();
                   win->show();
               }});
           });


           });

        }

   }




}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap map;//主场景对象
    QPixmap title;//主场景标题
    title.load(":/res/Title.png");
    map.load(":/res/PlayLevelSceneBg.png");//加载图片
    painter.drawPixmap(0,0,this->width(),this->height(),map);//绘制图片，并且按照实际情况进行拉伸
    painter.drawPixmap(10,30,title);//绘制标题图片
}
void PlayScene::backtochoose(QMainWindow*a)
{

        connect(btn_back,&MyButton::clicked,[=](){
            btn_back->zoom();
            QTimer::singleShot(200,this,[=](){
                this->hide();
                a->show();

            });

        });//点击按钮后返回主窗口
}
void PlayScene::Helpersendtips()
{

    connect( tipsaction,&QAction::triggered,[=](){



        //玩家已经开始走了，先比较一下玩家的路径和答案的路径
        bool same=true;
        int border;
        border=helper.size()<=answer.size()?helper.size():answer.size();
        for(int i=0;i<border;i++)//先确定哪个元素比较多
        {
            if(helper[i]->x!=answer[i]->x||helper[i]->y!=answer[i]->y)//比较路径是否相等
            {
                same=false;
                ifadd=true;
            }
        }
            if(same)
            {
                tip=new tips(answer[helper.size()]);//传输一步正确的
                ifadd=true;
            }
            else
            {
                tip=new tips(helper[helper.size()-1]);//先返回到最初的设定
                ifadd=false;
                comparation=new path(helper[helper.size()-1]->x,helper[helper.size()-1]->y);

                helper.pop_back();
            }


    tip->backtoplay(this);
    tip->show();
    });
}
void PlayScene::godhand()
{
    connect(god,&QAction::triggered,[=](){




        bool same=true;
        int border;
        border=helper.size()<=answer.size()?helper.size():answer.size();
        for(int i=0;i<border;i++)//先确定哪个元素比较多
        {
            if(helper[i]->x!=answer[i]->x||helper[i]->y!=answer[i]->y)//比较路径是否相等
            {
                same=false;
                ifadd=true;
            }
        }

            if(same)
            {
                if(answer.size()-1==helper.size())
                {
                    ifwin=true;
                }//如果已经走到了倒数第二步了，那么下面的程序就是把最后一步走完，所以这里直接将ifwin设为true
                coinset[answer[helper.size()]->x-1][answer[helper.size()]->y-1]->changeFlag();
              int  i=answer[helper.size()]->x-1;
              int  j=answer[helper.size()]->y-1;
                QTimer::singleShot(100,this,[=](){
                    if(coinset[i][j]->posx+1<=4)
                    {
                        coinset[i+1][j]->changeFlag();
                        array[i+1][j]=!(array[i+1][j]);
                    }//检测右边是否有硬币需要翻转
                    if(coinset[i][j]->posx-1>=1)
                    {
                        coinset[i-1][j]->changeFlag();
                         array[i-1][j]=!(array[i-1][j]);
                    }//检测左边是否有硬币需要翻转
                    if(coinset[i][j]->posy+1<=4)
                    {
                        coinset[i][j+1]->changeFlag();
                         array[i][j+1]=!(array[i][j+1]);
                    }//检测下边硬币是否需要反转
                    if(coinset[i][j]->posy-1>=1)
                    {
                        coinset[i][j-1]->changeFlag();
                        array[i][j-1]=!(array[i][j-1]);
                    }//检测上边硬币是否需要反转
                });

                ifadd=true;
                if(ifadd)
               {

                helper.push_back(new path(i+1,j+1));//把外挂的路径压入向量

               }

            }
            else
            {    coinset[helper[helper.size()-1]->x-1][helper[helper.size()-1]->y-1]->changeFlag();
                //先返回到最初的设定
                int  i=helper[helper.size()-1]->x-1;
                int  j=helper[helper.size()-1]->y-1;
                  QTimer::singleShot(100,this,[=](){
                      if(coinset[i][j]->posx+1<=4)
                      {
                          coinset[i+1][j]->changeFlag();
                          array[i+1][j]=!(array[i+1][j]);
                      }//检测右边是否有硬币需要翻转
                      if(coinset[i][j]->posx-1>=1)
                      {
                          coinset[i-1][j]->changeFlag();
                           array[i-1][j]=!(array[i-1][j]);
                      }//检测左边是否有硬币需要翻转
                      if(coinset[i][j]->posy+1<=4)
                      {
                          coinset[i][j+1]->changeFlag();
                           array[i][j+1]=!(array[i][j+1]);
                      }//检测下边硬币是否需要反转
                      if(coinset[i][j]->posy-1>=1)
                      {
                          coinset[i][j-1]->changeFlag();
                          array[i][j-1]=!(array[i][j-1]);
                      }//检测上边硬币是否需要反转
                  });
                ifadd=false;
                helper.pop_back();//删除掉末尾的路径，不然会陷入死循环
                if(ifadd)
               {
                helper.push_back(new path(i+1,j+1));//把外挂的路径压入向量

               }


            }

            QTimer::singleShot(500,this,[=](){
                if(ifwin)
            {
               this->hide();
                win->show();
            }});
    });
}
void PlayScene::getwindow(QMainWindow*a)
{
    win->backtomainscene(a);
}
