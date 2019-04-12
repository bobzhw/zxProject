//
// Created by zhouwei on 19-3-25.
//

#include "Draw.h"
#include<cstring>
#include<unistd.h>
Point* Draw::point = new Point(-1,-1);
Line* Draw::line = new Line(new Point(-1,-1),new Point(-1,-1));
std::function<void()> Draw::callback_ = nullptr;

const float max_x = 1200.0;
const float max_y = 800.0;
void Draw::drawPoint(int size)
{
//    sleep(1);
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f((point->x)/max_x,(point->y)/max_y);
    glEnd();
    glFlush();
}



void Draw::setPoint(float x, float y)
{
    point->x = x;
    point->y = y;
}

void Draw::setLine(float x1, float y1, float x2, float y2)
{
    line->start_->x = x1;
    line->start_->y = y1;
    line->end_->x = x2;
    line->end_->y = y2;
}



void Draw::drawLine()
{
//    sleep(1);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(line->start_->x/max_x,line->start_->y/max_y);
    glVertex2f(line->end_->x/max_x,line->end_->y/max_y);
    glEnd();
    glutSwapBuffers();
}


void Draw::draw(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1200,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("test");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glColor3f(1.0,1.0,1.0);
    glutDisplayFunc(drawFunction);
    glutMainLoop();
}

void Draw::setCallBack(std::function<void()>&& cb)
{
    callback_ = cb;
}


void Draw::drawPoint(float x,float y,int size)
{
    setPoint(x,y);
    drawPoint(size);
}

void Draw::drawLine(float x1,float y1,float x2,float y2)
{
    setLine(x1,y1,x2,y2);
    drawLine();
}

