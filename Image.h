
#ifndef _IMAGE
#define _IMAGE
#include "ShadowBuffer.h"
#include "Drawing.h"
#include "Point.h"
#include <cstring>

using namespace std;

class Image : public Drawing {
public:
    vector<Color> colors;
    Point position;

    Image();
    Image(vector<Point>& points, vector<Color>& colors);
    Image(Point points[], Color colors[], int n);
	Image(vector<Point>& points, vector<Color>& colors, Point position);

    void setPosition(Point p);
    

    void draw(ShadowBuffer &sb);
    void draw(ShadowBuffer &sb, int scaleX, int scaleY);

    Color ** getCached();
    Point& getWidthAndHeight();
};

#endif