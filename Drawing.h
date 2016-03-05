#ifndef _DRAWING
#define _DRAWING
#include "ClippingHelper.h"
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
        vector<Point> clippedPoints;

        Drawing();
        Drawing(Point points[], int n);
        Drawing(vector<Point>& points);

        virtual void draw(ShadowBuffer& sb)=0;

        virtual void rotate(Point axis, float angle);
        virtual void translate(float dX, float dY);
        virtual void scale(Point axis, float scalingFactorX, float scalingFactorY);
        virtual void clip(Point min, Point max, float scale);

        virtual Point * getTipPoints();
};

#endif
