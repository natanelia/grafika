#ifndef __SCANLINE
#define __SCANLINE

#include "Point.h"

class ScanLine {
public:
	vector<Point> sortVector(vector<Point> v);
	int findIntersection(Point& p1, Point& p2, int y, int &x);
	void scanLineFill(ShadowBuffer& sb, vector<Point> v);
	

    
};

#endif