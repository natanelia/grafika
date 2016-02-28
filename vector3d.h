#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cmath>
#define PI 3.14159265358979323846
using namespace std;

class vector3d
{
    //Terdiri dari sebuah titik (x,y,z) + void-void transformasi pendukung (rotasi, translasi, scaling)
    public:
        vector<float> point; //titik vektor
        vector< vector<float> > matrix; //matrix transformasi

        vector3d();
        vector3d(float x, float y, float z);
        virtual ~vector3d();

        //fungsi pendukung
        void transformation (); //melakukan transformasi "matrix" terhadap "point"
        void clearMatrix();
        void translation(float dx, float dy, float dz);
        void scale(float scaleX, float scaleY, float scaleZ);
        void rotateX(float degree); //ClockWise
        void rotateY(float degree);//ClockWise
        void rotateZ(float degree);//ClockWise

    protected:

    private:
};

#endif // VECTOR3D_H
