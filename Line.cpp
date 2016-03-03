#include "Line.h"

Line::Line(vector<Point>& points) : Drawing(points) {}

Line::Line(Point points[], int n) : Drawing(points, n) {}

Line::Line(Point p1, Point p2){
    points.push_back(p1);
    points.push_back(p2);
}

void Line::draw(ShadowBuffer& sb) {
    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;
    int x2 = (int)points[1].x;
    int y2 = (int)points[1].y;

    float deltaX = (x2 - x1);
    float deltaY = (y2 - y1);
    float error = 0;
    float deltaErr = fabs(deltaY/deltaX);

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    int y = (int)y1;
    for (int x = (int)x1; x <= (int)x2; x++) {
        sb.plot(x,y, color);
        error = error + deltaErr;

        while (error >= 0.5 && y != y2) {
            sb.plot(x,y, color);
            int sign = (y2 > y1) ? 1: -1;
            y = y + sign;
            error = error - 1;
        }
    }
}

Point Line::getPoint1(){
    return points[0];
}

Point Line::getPoint2(){
    return points[1];
}
