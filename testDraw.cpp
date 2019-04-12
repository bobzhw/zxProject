////
//// Created by zhouwei on 19-4-12.
////
//
//#include <iostream>
//#include<GL/glut.h>
//#include<functional>
//#include"Draw.h"
//#include<queue>
//#include<unordered_set>
//#include<string>
//using namespace std;
//
////draw the cross
//void drawCross()
//{
//    if(cross == nullptr)
//        return;
//    if(cross_container.find(cross)==cross_container.end())
//    {
//        Point *point = new Point(x,y);
//        cross_container[cross] = point;
//        Draw::drawPoint(point->x,point->y,10);
//        vector<Road*> vec = cross->getRoads();
//        for(int i =0;i<vec.size();i++)
//        {
//            if(vec[i]!=nullptr)
//            {
//
//                Cross* tmp = vec[i]->getStartCross() == cross ? vec[i]->getEndCross() : vec[i]->getStartCross();
//                switch (i)
//                {
//                    case 0:
//                    {
//
//                        drawCross(tmp,cross_container,road_container,x,y+100);
//                        break;
//                    }
//                    case 1:
//                    {
//                        drawCross(tmp,cross_container,road_container,x+100,y);
//                        break;
//                    }
//                    case 2:
//                    {
//                        drawCross(tmp,cross_container,road_container,x,y-100);
//                        break;
//                    }
//                    case 3:
//                    {
//                        drawCross(tmp,cross_container,road_container,x-100,y);
//                    }
//                }
//                if(road_container.find(vec[i]) == road_container.end())
//                {
//                    Line* line = new Line(cross_container[vec[i]->getStartCross()],cross_container[vec[i]->getEndCross()]);
//
//
//                    road_container[vec[i]] = line;
//                }
//            }
//
//        }
//    }
//
//
//}
//
//void drawCar(std::unordered_map<int ,Car*> maps,unordered_map<Cross*,Point*>& cross_container)
//{
//    for(const auto& it : maps)
//    {
//        Point* point = cross_container[it.second->getStartCross()];
//        Draw::drawPoint(*point,20);
//    }
//}
//
//void drawRoad(unordered_map<Road*,Line*> road_container)
//{
//    for(auto it = road_container.begin();it!=road_container.end();it++)
//    {
//        Draw::drawLine(*it->second);
//    }
//}
//
//void draw(Cross* cross,Map map)
//{
//    unordered_map<Cross*,Point*> cross_container;
//    unordered_map<Road*,Line*> road_container;
//    drawCross(cross,cross_container,road_container,400,200);
//    drawRoad(road_container);
//    drawCar(map.getCarManager()->getTMap(),cross_container);
//}
////int main(int argc,char**argv) {
////
////    Map maps("/home/zhouwei/桌面/huawei/hwProject/data/config_6/");
////    auto crossmap = maps.getCrossManager();
////    Cross* cross = crossmap->firstElement();
////    Draw::setCallBack(std::bind(&draw,cross));
////    Draw::draw(argc,argv);
////
////
////    return 0;
////}
//
//int main(int argc,char**argv)
//{
//    Map map("../data/config_1/");
//    auto crossmap = map.getCrossManager();
//    Cross* cross = crossmap->firstElement();
//    Draw::setCallBack(std::bind(&draw,cross,map));
//    Draw::draw(argc,argv);
//}