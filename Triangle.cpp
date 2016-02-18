#ifndef __TRIANGLE
#define __TRIANGLE

#include "Point.cpp"

class Triangle {
public:
    Point P1;
    Point P2;
    Point P3;
    
    Triangle() {

    }
    Triangle (Point _P1, Point _P2, Point _P3){
        P1.x=_P1.x;
        P1.y=_P1.y;
        P2.x=_P2.x;
        P2.y=_P2.y;
        P3.x=_P3.x;
        P3.y=_P3.y;
    }
};

#endif