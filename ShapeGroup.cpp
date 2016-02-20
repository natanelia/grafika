#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(string objName) {
    Util util;
    map<string, vector<Point> > point = util.readObject("peta.txt");
    vector<vector<Point> > points = util.convertPoint(point, objName, 0, 0, 10, 10);

    cout<< points.size()<<endl;
    for (int j = 0; j < points.size(); j++) {
        Shape shape(points[j]);
        shapes.push_back(shape);
        cout<< points[j].size() <<endl;
    }
}

void ShapeGroup::draw(ShadowBuffer& sb) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].draw(sb);
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
    }
}

void ShapeGroup::rotate(Point axis, float angle) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].rotate(axis, angle);
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
