#ifndef _DRAWING
#define _DRAWING
#include "Point.h"
#include "Color.h"
#include "ShadowBuffer.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265358979323846

using namespace std;

class Drawing {
    public:
        Point anchor;
        vector<Point> points;
        vector<Point> clippedPoint;

        Drawing() {}
        Drawing(Point points[], int n);
        Drawing(vector<Point>& points);

        virtual void draw(ShadowBuffer& sb)=0;

        virtual void rotate(Point axis, float angle);
        virtual void translate(float dX, float dY);
        virtual void scale(Point axis, float scalingFactorX, float scalingFactorY);

        virtual Point * getTipPoints();
        virtual void clip(Point min, Point max, float scale);
        virtual int getBinaryCode(Point P, Point min, Point max);
        virtual Point* getIntersection(Point P, Point Q, Point min, Point max);
        virtual int andBinary(int code1, int code2);
        virtual Point findNearestPoint(Point P, Point min, Point max);
};
#endif
