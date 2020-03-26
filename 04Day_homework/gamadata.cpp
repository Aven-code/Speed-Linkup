#include "gamadata.h"
#include <cstdlib>
#include <ctime>
#include <QDebug>

int data[ROWS][COLS] ={
        1,2,3,4,
        3,2,1,4,
        5,6,5,6,
};

void init()
{

    //[1]初始化
    int temp = 0;
    for(int i=0;i< ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
        {
            //初始化使二维数组中有相同的元素
            data[i][j] = temp/2 +1;
            temp++;
        }

    }

   //[2]打乱顺序
   srand((unsigned)time(nullptr));
   for(int i=0;i< ROWS * COLS /2;i++)
   {
        int x1 = rand() % COLS;
        int x2 = rand() % COLS;
        int y1 = rand() % ROWS;
        int y2 = rand() % ROWS;
        int temp = data[y1][x1];
        data[y1][x1] = data[y2][x2];
        data[y2][x2] = temp;
   }



}

/*
    将被消除的按钮所代表的data数组中的值变为0
*/
void clearData(QPushButton * firstBtm,QPushButton * lastBtm)
{
    int x1,x2,y1,y2;
    x1 = firstBtm->x() /75;
    y1 = firstBtm->y() /75;

    x2 = lastBtm->x() /75;
    y2 = lastBtm->y() /75;

   qDebug() << "(y1,x1) :" << y1 << "." << x1;
   qDebug() << "(y2,x2) :" << y2 << "." << x2;

   qDebug() << "-----------------";
   qDebug() << "data[ "<< y1 << "] [" << x1 <<"] :" << data[y1][x1];
   qDebug() << "data[ "<< y2 << "] [" << x2 <<"] :" << data[y2][x2];
   qDebug() << "-----------------";
    data[y1][x1] = 0;
    data[y2][x2] = 0;
    qDebug() << "-----------------";


    qDebug() << "data[ "<< y1 << "] [" << x1 <<"] :" << data[y1][x1];
    qDebug() << "data[ "<< y2 << "] [" << x2 <<"] :" << data[y2][x2];

    qDebug() << "-----clearData()------------";


}

//规则1 直线相消除
bool gameRule(QPushButton * firstBtm,QPushButton * lastBtm)
{
    int x1,x2,y1,y2;

    x1 = firstBtm->x() /75;
    y1 = firstBtm->y() /75;

    x2 = lastBtm->x() /75;
    y2 = lastBtm->y() /75;


    if(data[y1][x1] == data[y2][x2])    //首先值的相同,如果值不相同就没必要判断了
    {

        if(x1 == x2 && y1 == y2)
        {
             return false;
        }

        if(lineCore(x1,y1,x2,y2))
        {
            return true;
        }

    }

    return false;

}

//直线消除核心code
bool lineCore(int x1,int y1,int x2,int y2)
{
       //行的判断
       if(y1 == y2)    //如果在同一行，也就是x+1 ,y不变就能找到对方
       {
           qDebug() << " 114: if(y1 == y2) ";
//           if(y1 == ROWS || y1 == -1)   //行边界判断
//           {
//                qDebug() << "117: if(y1 == ROWS || y1 == -1)  ";
//                return true;
//           }
           if(x1 > x2)
           {
               qDebug() << "122: if(x1 > x2)  ";
               int temp_x = x1;
               x1 = x2;
               x2 = temp_x;
           }

            int  sum = 0;
           for(int var_x = x1+1;var_x<x2;var_x++)
           {
               sum += data[y1][var_x];
               qDebug() << "132:x "<<sum ;
           }
           if(0 == sum)
           {
               qDebug() << " 136if(0 == sum) ";
               return true;
           }
        }

       //列的判断
       if(x1 == x2)
       {
            qDebug() << " 144:if(x1 == x2) ";
//           if(x1 == COLS ||x1 == -1)   //行边界判断
//           {
//               qDebug() << " 147: if(x1 == COLS ||x1 == -1)  ";
//               return true;
//           }

           if(y1 > y2)
           {
               qDebug() << " 153:   if(y1 > y2)  ";
               int temp_y = y1;
               y1 = y2;
               y2 = temp_y;
           }

           int  sum = 0;
           for(int var_y = y1+1;var_y<y2;var_y++)
           {
               sum += data[var_y][x1];
               qDebug() << "163:y "<<sum ;
           }
           if(0 == sum)
           {
               qDebug() << "167: if(0 == sum)  ";
               return true;
           }

       }

    return false;
}

//转弯一次可以消除核心code
bool oneTurnCore(int x1,int y1,int x2,int y2)
{

    qDebug() << "180: bool oneTurnCore(int x1,int y1,int x2,int y2) ";
    int assumedX = x1;
    int assumedY = y2;//目标在左边的时
    qDebug() << "184:  if(lineCore(x1,y1,assumedX,assumedY)) ";
    if(lineCore(x1,y1,assumedX,assumedY) && data[assumedY][assumedX]==0)
    {
        qDebug() << "186:if(lineCore(assumedX,assumedY,x2,y2)) ";
        if(lineCore(assumedX,assumedY,x2,y2))
        {
            qDebug() << " 189:if(lineCore(assumedX,assumedY,x2,y2)) ";
            return true;
        }
    }


     assumedX = x2;
     assumedY = y1; //往下走
    qDebug() << " 197: if(lineCore(x1,y1,assumedX,assumedY))";
    if(lineCore(x1,y1,assumedX,assumedY)  && data[assumedY][assumedX]==0)
    {
         qDebug() << " 200:if(lineCore(x1,y1,assumedX,assumedY)) ";
        if(lineCore(assumedX,assumedY,x2,y2))
        {
            qDebug() << " 203:if(lineCore(x1,y1,assumedX,assumedY)) ";
            return true;
        }
    }



}



//规则2 转弯一次可以消除
bool gameRule2(QPushButton * firstBtm,QPushButton * lastBtm)
{
    int x1,x2,y1,y2;
    x1 = firstBtm->x() /75;
    y1 = firstBtm->y() /75;

    x2 = lastBtm->x() /75;
    y2 = lastBtm->y() /75;


 if(data[y1][x1] == data[y2][x2])    //首先值的相同
 {

    //如果两次点的是同一个位置就返回false
     if(x1 == x2 && y1 == y2)
     {
          return false;
          qDebug() << "232 if(x1 == x2 && y1 == y2)" ;
     }

     if(oneTurnCore(x1,y1,x2,y2))
     {
          qDebug() << "237 if(oneTurnCore(x1,y1,x2,y2))" ;
          return true;

     }
 }

    return false;

}


//规则3 转弯两次可以消除
bool gameRule3(QPushButton * firstBtm,QPushButton * lastBtm)
{
    int x1,x2,y1,y2;
    x1 = firstBtm->x() /75;
    y1 = firstBtm->y() /75;

    x2 = lastBtm->x() /75;
    y2 = lastBtm->y() /75;


    if(data[y1][x1] == data[y2][x2])    //值必须相同
    {
        //如果两次点的是同一个位置就返回false
        if(x1 == x2 && y1 == y2)
        {
             return false;
        }


        //先从列(x)的层面来讲，一共会出现三种情况，x1 == x2 x1 < x2 x1 > x2
        if(x1 == x2)
        {
             //第一个假想敌
           // int assumedY1 = y1;
           // int assumedY2 = y2;
             int assumedX1 = x1;

             //第二个假想敌
             int assumedX2 = x2;

             //如果从右边出发
             for(int i=1;i<COLS;i++)
             {
                 if((lineCore(x1,y1,assumedX1+i,y1)&& data[y1][assumedX1+i]==0)&&
                     (lineCore(x2,y2,assumedX2+i,y2)&& data[y2][assumedX2+i]==0) &&
                     lineCore(assumedX1+i,y1,assumedX2+i,y2))
                 {
                     return true;
                 }
                  if(assumedX1 + i == COLS)//  如果我右移到边界还没通，就跳出循环
                  {
                      break;
                  }
             }

             //如果从左边出发
             for(int i=1;i<COLS;i++)
             {
                   if((lineCore(x1,y1,assumedX1-i,y1) && data[y1][assumedX1-i]==0)&&
                       (lineCore(x2,y2,assumedX2-i,y2) && data[y2][assumedX2+i]==0) &&
                       lineCore(assumedX1-i,y1,assumedX2-i,y2))
                   {
                       return true;
                   }
                   if(assumedX1-i == -1)//  如果我左移到边界还没通，就跳出循环
                   {
                       break;
                   }
             }

        }

        if(x1 > x2)
        {
            int temp_x = x1,temp_y = y1;
            x1 = x2;
            x2 = temp_x;

            y1 = y2;
            y2 = temp_y;

        }

        if(x1 < x2)
        {
            //设假想敌
            int assumedY = y1;  //先去这个目标那里看能都行得通
            int assumedX = x1;
            for(int i = 1;i<COLS;i++)   //想右走
            {
                //先看我自己能不能右移
                if(lineCore(x1,y1,assumedX+i,y1) && data[y1][assumedX+i]==0)
                {
                    if(oneTurnCore(assumedX+i,y1,x2,y2))
                    {
                        return true;
                    }
                    if(assumedX+i == COLS)  //  如果我右移到边界还没通，就跳出循环
                    {
                        break;
                    }
                }else
                {
                    break;
                }
            }

            for(int i=1;i<COLS;i++)
            {
                //先看我自己能不能左移
                if(lineCore(x1,y1,assumedX-i,y1) && data[y1][assumedX-i]==0 )
                {
                    if(oneTurnCore(assumedX-i,y1,x2,y2))
                    {
                        return true;
                    }
                    if(assumedX-i == -1)  //  如果我左移到边界还没通，就跳出循环
                    {
                        break;
                    }
                }else
                {
                    break;
                }

            }

        }


 //-----------------行列分界线


        //该从行(y)的层面来讲，一共会出现三种情况，y1 == y2 y1 < y2 y1 > y2
        if(y1 == y2)
        {
             //第一个假想敌
             int assumedY1 = y1;

             //第二个假想敌
             int assumedY2 = y2;


             //如果从下面出发
             for(int i=1;i<ROWS;i++)
             {
                   if((lineCore(x1,y1,x1,assumedY1+i) && data[assumedY1+i][x1]==0)&&
                       (lineCore(x2,y2,x2,assumedY2+i)&& data[assumedY2+i][x2]==0) &&
                       lineCore(x1,assumedY1+i,x2,assumedY2+i))
                   {
                       return true;
                   }
                   if(assumedY1 + i == ROWS) //如果我下移到边界还没通，就跳出循环
                   {
                        break;
                   }
             }

             //如果从上边出发
             for(int i=1;i<ROWS;i++)
             {
                   if((lineCore(x1,y1,x1,assumedY1-i) && data[assumedY1-i][x1]==0)&&
                      (lineCore(x2,y2,x2,assumedY2-i)&& data[assumedY2-i][x2]==0) &&
                       lineCore(x1,assumedY1-i,x2,assumedY2-i))
                   {
                       return true;
                   }
                   if(assumedY1 - i == -1) //如果我上移到边界还没通，就跳出循环
                   {
                       break;
                   }
             }

        }

        if(y1 > y2)
        {
            int temp_x = x1;
            x1 = x2;
            x2 = temp_x;

            int temp_y = y1;
            y1 = y2;
            y2 = temp_y;

        }

        if(y1 < y2)
        {
            //设假想敌
            int assumedY = y1;  //先去这个目标那里看能都行得通
            int assumedX = x1;

            //反向往下走+
            for(int i = 1;i<ROWS;i++)
            {
                //先看我自己能不能下移
                if(lineCore(x1,y1,x1,assumedY+i) && data[assumedY+i][x1] == 0)
                {
                    if(oneTurnCore(x1,assumedY+i,x2,y2))
                    {
                        return true;
                    }
                    if(assumedY+i == ROWS)  //  如果我下移到边界还没通，就跳出循环
                    {
                        break;
                    }
                }else
                {
                    break;
                }
            }

             //反向往上走-
            for(int i=1;i<ROWS;i++)
            {
                //先看我自己能不能上移
                if(lineCore(x1,y1,x1,assumedY-i) && data[assumedY-i][x1])
                {
                    if(oneTurnCore(x1,assumedY-i,x2,y2))
                    {
                        return true;
                    }
                    if(assumedY-i == -1)  //  如果我左移到边界还没通，就跳出循环
                    {
                        break;
                    }
                }else
                {
                    break;
                }

            }

        }


    }

    return false;
}


/*
    边缘检测
*/
bool edgeCheck(QPushButton * firstBtm,QPushButton * lastBtm)
{
    int x1,x2,y1,y2;
    x1 = firstBtm->x() /75;
    y1 = firstBtm->y() /75;

    x2 = lastBtm->x() /75;
    y2 = lastBtm->y() /75;

    if((data[y1][x1] != data[y2][x2]) || (x1 == x2 && y1 == y2))    //值必须相同且 不能是同一个按键
    {
        return false;
    }

    if((x1-1 == -1 && x2-1 == -1)||
           (y1+1==ROWS && y2+1 == ROWS)||
            (x1+1 == COLS && x2+1 == COLS)||
           (y1-1== -1 && y2-1 == -1))
    {
        qDebug() << "bool edgeCheck(QPushButton * firstBtm,QPushButton * lastBtm" ;
        return true;
    }

  return false;
}
