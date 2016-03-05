#ifndef __SHAPE
#define __SHAPE
#include "ShadowBuffer.h"
#include "Drawing.h"
#include "Line.h"
//#include "FillHelper.h"
//#include "Triangle.h"
//#include "Triangulate.h"

class Shape : public Drawing {
protected:
    int findIntersection(Point& p1, Point& p2, int y, int &x);
    void scanLineFill(ShadowBuffer& sb, vector<Point> v);
    void drawAvailable(vector<Line> available, vector<Point> demand, ShadowBuffer& sb, Color c); 
    vector<Line> initAvailable(vector<Point> v, ShadowBuffer& sb); 

public:
    //int type;
    Color color;
    Color borderColor;

    Shape();
    Shape(vector<Point>& points);
    Shape(Point points[], int n);
    ~Shape();

    vector<Point> sortVector(vector<Point> v);
    void draw(ShadowBuffer& sb);
    void drawClipped(ShadowBuffer& sb, Point min, Point max, float scale);
	void drawBorder(ShadowBuffer& sb, Color c);
    
    void scanLineIntersect(ShadowBuffer& sb, Shape available);
    void setColor(Color color);
};

#endif