#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(string objName) {
    Util util;
    map<string, vector<Point> > point = util.readObject("peta.txt");
    vector<vector<Point> > points = util.convertPoint(point, objName, 0, 0, 10, 10);

    for (int j = 0; j < points.size(); j++) {
        Shape shape(points[j]);
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
