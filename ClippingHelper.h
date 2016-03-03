#ifndef __CLIPPINGHELPER
#define __CLIPPINGHELPER

#include "Point.h"

class ClippingHelper {
public:
    static int getBinaryCode(Point P, Point min, Point max);
    static Point* getIntersection(Point P, Point Q, Point min, Point max);
    static int andBinary(int code1, int code2);
    static Point findNearestPoint(Point P, Point min, Point max);
};

#endif