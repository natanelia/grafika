#ifndef __POINT
#define __POINT

class Point {
public:
    float x;
    float y;

    Point() {
        this->x = 0;
        this->y = 0;
    }
    Point(float x, float y){
        this->x = x;
        this->y = y;
    }
    Point(const Point& p) {
        this->x = p.x;
        this->y = p.y;
    }
};

#endif