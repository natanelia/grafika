#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(string objName) {
    Util util;
    map<string, vector<Point> > point = util.readObject("peta.txt");
    vector<vector<Point> > points = util.convertPoint(point, objName, 0, 0, 10, 10);

    for (int j = 0; j < points.size(); j++) {
        Shape shape(points[j]);
        shape.color= Color(225,0,0);
        shapes.push_back(shape);
    }
}

void ShapeGroup::draw(ShadowBuffer& sb) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].draw(sb);
        Color c(225,225,0);
        //shapes[i].drawBorder(c, sb);
    }
}

void ShapeGroup::drawView(ShadowBuffer& sb) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].drawView(sb);
    }
}

void ShapeGroup::translate(float dX, float dY) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].translate(dX, dY);
    }
}

void ShapeGroup::scale(Point axis, float scalingFactorX, float scalingFactorY) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].scale(axis, scalingFactorX, scalingFactorY);

        /*for (int i = 0 ; i < shapes[i].points.size() ; i++){
            shapes[i].points[i].x += axis.x;
            shapes[i].points[i].y +=  axis.y;
            shapes[i].points[i].x *= scalingFactorX;
            shapes[i].points[i].y *=  scalingFactorY;
            shapes[i].points[i].x -= axis.x;
            shapes[i].points[i].y -=  axis.y;
        }*/
    }
}

void ShapeGroup::rotate(Point axis, float angle) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].rotate(axis, angle);
    }
}

void ShapeGroup::clip(Point min, Point max, float scale) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].clip(min,max,scale);
    }
}


Point * ShapeGroup::getTipPoints() {
    Point * tipPoints = shapes[0].getTipPoints();

    for (int i = 1; i < shapes.size(); i++) {
        Point * tp = shapes[i].getTipPoints();
        if (tipPoints[0].x > tp[0].x) {
            tipPoints[0].x = tp[0].x;
        }

        if (tipPoints[0].y > tp[0].y) {
            tipPoints[0].y = tp[0].y;
        }

        if (tipPoints[1].x < tp[1].x) {
            tipPoints[1].x = tp[1].x;
        }

        if (tipPoints[1].y < tp[1].y) {
            tipPoints[1].y = tp[1].y;
        }
    }

    return tipPoints;
}

void ShapeGroup::splitAvailable(vector<vector<Line> > &Available, vector<Point> demand, ShadowBuffer& sb, Color c){
    vector<Line> available= Available.back();
    for(int i= 0; i < available.size(); i++ ){
        int j=0;
        vector<Line> newAvailable;
        for(j=0; j<demand.size();j+=2){
            if(available[i].getPoint2<=available[i].getPoint1){//sudah tidak ada slot
                newAvailable.push_back(available[i]);   
                break;
            }
            if(demand[j].x > available[i].getPoint2.x){//demand berada di kanan available
                newAvailable.push_back(available[i]); 
                break;
            }
            if(demand[j+1].x < available[i].getPoint1.x){ //demand di kiri available
                newAvailable.push_back(available[i]); 
                continue;
            }
            if((available[i].getPoint1.x <= demand[j].x)&&(demand[j+1].x <= available[i].getPoint2.x)){ //demand berada di tengah
                // vector<Point> temp, temp2;
                // Point p1 = available[i].getPoint1;
                // Point p2(demand[j].x-1, available[i].getPoint1.y);
                // temp.push_back(p1);
                // temp.push_back(p2);
                // Line split1(temp);
                Line split1(available[i].getPoint1, Point(demand[j].x-1, available[i].getPoint1.y));

                // Point p3(demand[j+1].x+1,available[i].getPoint2.y);
                // Point p4 = available[i].getPoint2;
                // temp2.push_back(p3);
                // temp2.push_back(p4);
                // Line split2(temp2);
                Line split2(Point(demand[j+1].x+1,available[i].getPoint2.y), available[i].getPoint2);

                newAvailable.push_back(split1);
                newAvailable.push_back(split2);

                // vector<Point> d;
                // d.push_back(demand[j]);
                // d.push_back(demand[j+1]);
                // Line line(d);
                Line line(demand[j], demand[j+1]);
                line.color = c;
                line.draw(sb);

            }else if(available[i].getPoint1.x <= demand[j].x){ //demand lebih banyak kebelakang
                // vector<Point> temp;
                // Point p1 = available[i].getPoint1;
                // Point p2(demand[j].x-1, available[i].getPoint1.y);
                // temp.push_back(p1);
                // temp.push_back(p2);

                Line split(available[i].getPoint1, Point(demand[j].x-1, available[i].getPoint1.y));
                newAvailable.push_back(split);

                // vector<Point> d;
                // d.push_back(demand[j]);
                // d.push_back(Point(available[i].getPoint2.x,demand[j].y));
                Line line(demand[j], Point(available[i].getPoint2.x,demand[j].y));
                line.color = c;
                line.draw(sb);

            }else if(demand[j+1].x <= available[i].getPoint2.x){ //demand lebih banyak di depan
                // vector<Point> temp;
                // Point p3(demand[j+1].x+1,available[i].getPoint2.y);
                // Point p4 = available[i].getPoint2;
                // temp.push_back(p3);
                // temp.push_back(p4);
                Line split(Point(demand[j+1].x+1,available[i].getPoint2.y), available[i].getPoint2);

                // vector<Point> d;
                // d.push_back(Point(available[i].getPoint1.x,demand[j+1].y));
                // d.push_back(demand[j+1]);
                Line line(Point(available[i].getPoint1.x,demand[j+1].y),demand[j+1]);
                line.color = c;
                line.draw(sb);

                newAvailable.push_back(split);
            }

        }

    }
    //update info available
    Available.push_back(newAvailable);
}

void ShapeGroup::scanLineFill3D(ShadowBuffer& sb)
{    
    vector<vector<Line> > tersedia;
    vector<Line> init;
    vector<Point> pi;
    pi.push_back(Point(0,0));
    pi.push_back(Point(1020,0));
    Line l(pi);
    init.push_back(l);
    tersedia.push_back(init);


    Point p1, p2;   
    vector<Point> ListOfIntersectPoints;
    int edgesSize = v.size();
    int a=0;
    for(int i = 0; i <= 800; i++) {

        for(int j = 0; j < edgesSize; j++) {
            if(j != (edgesSize - 1)){
                p1 = v[j];
                p2 = v[j+1];
            }else{
                p1 = v[j];
                p2 = v[0];
            }
            int intersectX;
            if (findIntersection(p1,p2,i,intersectX)){
                if(p1.y > p2.y){
                    std::swap(p1,p2);
                }
                Point intersect(intersectX, i);
                if(intersect.y == p2.y)
                    continue;
                    ListOfIntersectPoints.push_back(intersect);
                    }
            }
            vector<Point> result = sortVector(ListOfIntersectPoints);
            int intersectPointsSize = result.size();
            Color d(225-a, 200-a, 200-a);
            a+=10;
            //for(int j = 0; j < intersectPointsSize-1; j+=2) {
                splitAvailable(tersedia, result, sb, d)
                    // vector<Point> p;
                    // p.push_back(result[j]);
                    // p.push_back(result[j+1]);
                    // Line line(p);
                    // line.color = this->color;
                    // line.draw(sb);
                    //drawLine(result[j].x,result[j].y,result[j+1].x,result[j+1].y,d);
            //}
            ListOfIntersectPoints.erase(ListOfIntersectPoints.begin(),ListOfIntersectPoints.end());
    }
}

void ShapeGroup::scanLineFill3DTandingan(vector<vector<vector3D> > v,ShadowBuffer& sb)
{    
    vector<vector<Line> > tersedia;
    vector<Line> init;
    vector<Point> pi;
    pi.push_back(Point(0,0));
    pi.push_back(Point(1020,0));
    Line l(pi);
    init.push_back(l);
    tersedia.push_back(init);


    Point p1, p2;   
    vector<Point> ListOfIntersectPoints;
    int edgesSize = v.size();
    int a=0;
    for(int i = 0; i <= 800; i++) {
        
        for(int j = 0; j < edgesSize; j++) {
            if(j != (edgesSize - 1)){
                p1 = v[j];
                p2 = v[j+1];
            }else{
                p1 = v[j];
                p2 = v[0];
            }
            int intersectX;
            if (findIntersection(p1,p2,i,intersectX)){
                if(p1.y > p2.y){
                    std::swap(p1,p2);
                }
                Point intersect(intersectX, i);
                if(intersect.y == p2.y)
                    continue;
                    ListOfIntersectPoints.push_back(intersect);
                    }
            }
            vector<Point> result = sortVector(ListOfIntersectPoints);
            int intersectPointsSize = result.size();
            Color d(225-a, 200-a, 200-a);
            a+=10;
            //for(int j = 0; j < intersectPointsSize-1; j+=2) {
                splitAvailable(tersedia, result, sb, d)
                    // vector<Point> p;
                    // p.push_back(result[j]);
                    // p.push_back(result[j+1]);
                    // Line line(p);
                    // line.color = this->color;
                    // line.draw(sb);
                    //drawLine(result[j].x,result[j].y,result[j+1].x,result[j+1].y,d);
            //}
            ListOfIntersectPoints.erase(ListOfIntersectPoints.begin(),ListOfIntersectPoints.end());
    }
}