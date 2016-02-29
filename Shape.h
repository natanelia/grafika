#ifndef __SHAPE
#define __SHAPE
#include "ShadowBuffer.h"
#include "Drawing.h"
#include "Line.h"
#include "Triangle.h"
#include "Triangulate.h"

class Shape : public Drawing {
protected:
    vector<Point> listAllPointinLine (Point P1, Point P2);
    void fillTriangle(Point P1, Point P2, Point P3, Color c, ShadowBuffer& sb);

public:
    Color color;

    Shape(vector<Point>& points);
    Shape(Point points[], int n);
    ~Shape();

    vector<Point> sortVector(vector<Point> v);
    int findIntersection(Point& p1, Point& p2, int y, int &x);
    void scanLineFill(vector<Point> v, ShadowBuffer& sb);
    void draw(ShadowBuffer& sb);
    void drawView(ShadowBuffer& sb);
	void drawBorder(Color c, ShadowBuffer& sb);
    void setColor(Color color);
};

#endif