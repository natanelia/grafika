#ifndef __SHAPEGROUP
#define __SHAPEGROUP
#include "ShadowBuffer.h"
#include "Shape.h"
#include "util.cpp"

class ShapeGroup {
protected:
    void projectTo2D(float offsetX, float offsetY);
    void splitAvailable(vector<Line>  &available, vector<Point> demand, ShadowBuffer& sb, Point basePoint, int textureWidth, int textureHeight, Color ** textureCache );
    void splitAvailable(vector<Line> &available, vector<Point> demand, Color c, ShadowBuffer& sb);
    void sortLayer();
    void scanLineFill3D(ShadowBuffer& sb);
    int findZMax(vector<Point> plane);
    int findIntersection(Point& p1, Point& p2, int y, int &x, int &z);
    void scanLineFill3D(ShadowBuffer& sb, Shape form); 
    vector<vector<Line> > initAvailable(int x1, int x2);
    vector<Line> initAvailable(vector<Point> v);
    vector<Point> sortVector(vector<Point> v);
    bool isOnShape(Shape des, Shape src);
    Point * getProjected3DTipPoints(); 
    Point findIntersection(vector<Point> line, vector<Point> plane);
    int getFront(vector<Point> plane1, vector<Point> plane2);
    
public:
    Color color;
    vector<Shape> shapes;
    vector<vector<Point> > pointToPrint;

    ShapeGroup(string objName, float offsetX, float offsetY, int scale);

    void draw(ShadowBuffer& sb, float offsetX, float offsetY);
    void drawClipped(ShadowBuffer& sb, Point min, Point max, float scale);
    void translate(float dX, float dY,float dZ);
    void scale(float scaleX, float scaleY, float scaleZ, float offsetX, float offsetY, float offsetZ);
    void rotateX(float degree, float offsetX, float offsetY, float offsetZ);
    void rotateY(float degree, float offsetX, float offsetY, float offsetZ);
    void rotateZ(float degree, float offsetX, float offsetY, float offsetZ);
    void build3D(int height, Point& lightSource, int const lightRadius);

    Point * getTipPoints();
    Point * getGroundTipPoints();
    Point * get3DTipPoints();
};

#endif