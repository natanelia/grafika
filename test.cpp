#ifndef __TEST

#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"
#include "Line.h"
#include "Shape.h"
#include "ShapeGroup.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>

class Test {
public:
    void testShape() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        map<string, vector<Point> > point = util.readObject("point.txt");
        Shape shape(util.convertPoint(point, "Baling", 0, 0, 0, 2, 2, 2)[0]);
        Point * tipPoints = shape.getTipPoints();
        Point ma((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2, 0 );
        shape.scale(ma, 5, 5);

        for (int i = 0; i < 360; i++) {
            Point * tipPoints = shape.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2, 0 );
            shape.rotate(midAxis, 5);
            shape.scale(midAxis, 1.005, 1.005);
            shape.color = Color(rand() % 255, rand() % 255, rand() % 255);

            sb.clear();
            shape.draw(sb);
            fb.draw(sb);
        }
    }
};

#endif
