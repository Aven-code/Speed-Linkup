#ifndef GAMADATA_H
#define GAMADATA_H
#include <QPushButton>
const unsigned short ROWS = 4;
const unsigned short COLS = 4;

extern int data[ROWS][COLS];

/*
    初始化游戏
*/
void init();

/*
    游戏规则1 直线相消除
*/
bool gameRule(QPushButton * firstBtm,QPushButton * lastBtm);


/*
    游戏规则2 转弯一次可以消除
 */
bool gameRule2(QPushButton * firstBtm,QPushButton * lastBtm);

/*
    游戏规则3 转弯两次可以消除
 */
bool gameRule3(QPushButton * firstBtm,QPushButton * lastBtm);


//直线消除核心
bool lineCore(int x1,int y1,int x2,int y2);

//一个弯消除核心
bool oneTurnCore(int x1,int y1,int x2,int y2);

/*
   清除
*/
void clearData(QPushButton * firstBtm,QPushButton * lastBtm);

//边缘检测
bool edgeCheck(QPushButton * firstBtm,QPushButton * lastBtm);
#endif // GAMADATA_H
