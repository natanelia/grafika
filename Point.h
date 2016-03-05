#ifndef POINT_H
#define POINT_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#define PI 3.14159265358979323846
using namespace std;

class Point
{
    //Terdiri dari sebuah titik (x,y,z) + void-void transformasi pendukung (rotasi, translasi, scaling)
    public:
        float x;
        float y;
        float z;
        float tag;

        Point();
        Point(float xnew, float ynew, float znew);
        virtual ~Point();

        //fungsi pendukung
        void transformation (float (&matrix)[4][4]); //melakukan transformasi "matrix" terhadap "point"
        void translation(float dx, float dy, float dz);
        void scale(float scaleX, float scaleY, float scaleZ);
        void rotateX(float degree); //ClockWise
        void rotateY(float degree);//ClockWise
        void rotateZ(float degree);//ClockWise
        
        void setX(float xnew);
        void setY(float ynew);
        void setZ(float znew);

        float getDistance(Point p2);

    protected:

    private:
};

#endif // POINT_H