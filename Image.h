
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
    Point projectPos;

    Image();
    Image(vector<Point>& points, vector<Color>& colors);
    Image(Point points[], Color colors[], int n);
	Image(vector<Point>& points, vector<Color>& colors, Point position);

    void setPosition(Point p);
    void project2dPos();

    void draw(ShadowBuffer &sb);
    void draw(ShadowBuffer &sb, int scaleX, int scaleY);
    void drawName(ShadowBuffer& sb);

    Color ** getCached();
    Point& getWidthAndHeight();
};

#endif