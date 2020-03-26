#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800,450);
    ui->setupUi(this);
    init();

   for(int y=0;y<ROWS;y++)
   {
       for(int x=0;x<COLS;x++)
       {
           buttons[y][x] = new QPushButton(this->centralWidget());
           buttons[y][x]->resize(75,75); //设置控件的大小
           buttons[y][x]->move(x*75,y*75);
           buttons[y][x]->setIconSize(QSize(75,75));
            buttons[y][x]->setCursor(Qt::PointingHandCursor);

           buttons[y][x]->setIcon(QIcon(QString( ":/image/image%1").arg(::data[y][x])));

           //建立槽函数
           connect(buttons[y][x],&QPushButton::clicked,this,&MainWindow::sendClicked);
       }
   }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendClicked()
{

    QPushButton *  button = dynamic_cast<QPushButton *>(sender());
    static QPushButton * lastBtm = nullptr;
    if(!lastBtm)
    {
        qDebug() << "first";
    }
    else
    {
        qDebug() << "second";
    }
    //如果上一次为null 说明这是第一次点击
    if(nullptr == lastBtm)
    {
        lastBtm = button;       //记录下来
    }
    else    //这是第二次点击
    {
        if(gameRule(lastBtm,button)
                || gameRule2(lastBtm,button)
               || gameRule3(lastBtm,button)
               || edgeCheck(lastBtm,button))
        {
            //加入游戏规则
            lastBtm->setEnabled(false);
            button->setEnabled(false);
            clearData(lastBtm,button);
        }

        lastBtm = nullptr;
    }



}
