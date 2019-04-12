//
// Created by zhouwei on 19-3-25.
//

#ifndef HWPROJECT_DRAW_H
#define HWPROJECT_DRAW_H
#include<functional>
#include<GL/glut.h>


using std::placeholders::_1;
using std::placeholders::_2;


class Point
{
public:
    float x;
    float y;
    Point(float x,float y)
    {
        this->x = x;
        this->y = y;
    }

};

class Line
{
public:
    Point* start_;
    Point* end_;
    Line(Point* start,Point* end)
        :   start_(start),end_(end)
    {}


};

class Draw
{
public:

    static void draw(int argc,char**argv);
    static void setCallBack(std::function<void()>&& cb);

    static void drawPoint(float x,float y,int size);
    static void drawLine(float x1,float y1,float x2,float y2);
    static void drawLine(Line line)
    {
        drawLine(line.start_->x,line.start_->y,line.end_->x,line.end_->y);
    }
    static void drawPoint(Point point,int size)
    {
        drawPoint(point.x,point.y,size);
    }
    static void drawLine(Point start,Point end)
    {
        drawLine(start.x,start.y,end.x,end.y);
    }
private:
    static Line* line;
    static Point* point;
    static void drawLine();
    static void setPoint(float x,float y);
    static void setLine(float x1,float y1,float x2,float y2);
    static void drawPoint(int size);
    static void drawFunction()
    {
        callback_();
    }

private:
    static std::function<void()> callback_;



};



#endif //HWPROJECT_DRAW_H
