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
    void drawShape() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        map<string, vector<Point> > point = util.readObject("point.txt");
        Shape shape(util.convertPoint(point, "Baling", 0, 0, 0, 2, 2, 2)[0]);
        Point * tipPoints = shape.getTipPoints();
        Point ma((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2, 0 , 0);
        shape.scale(ma, 5, 5);

        for (int i = 0; i < 360; i++) {
            Point * tipPoints = shape.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2, 0 , 0);
            shape.rotate(midAxis, 5);
            shape.scale(midAxis, 1.005, 1.005);
            shape.color = Color(rand() % 255, rand() % 255, rand() % 255);

            sb.clear();
            shape.draw(sb);
            fb.draw(sb);
        }
    }

    void drawLine() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        Line line(Point(0,0,0), Point(500, 500, 0));

        for (int i = 0; i < 500; i+=20) {
            sb.clear();
            line.draw(sb, Point(i,i,0), 500, Color(0,0,255), Color(255,255,0));
            fb.draw(sb);
        }
        usleep(500000);
    }

    void drawChoppedLine() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        Line line(Point(0,0,0), Point(500, 500, 0));

        for (int i = 0; i < 500; i+=5) {
            sb.clear();
            line.drawChopped(sb, Point(i,i,0), 707, Color(0,0,255), Color(255,255,0), 5);
            fb.draw(sb);
        }
        usleep(500000);
    }

    void drawMultiGradientLine() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        Line line(Point(0,0,0), Point(500, 500, 0));

        float * radius = new float[5];
        radius[0] = 0;
        radius[1] = 100;
        radius[2] = 200;
        radius[3] = 300;
        radius[4] = 400;

        Color * color = new Color[5];
        color[0] = Color(255, 0, 0);
        color[1] = Color(0, 255, 0);
        color[2] = Color(0, 0, 255);
        color[3] = Color(255, 0, 255);
        color[4] = Color(128, 255, 0);

        for (int i = 0; i < 500; i+=20) {
            sb.clear();
            line.draw(sb, Point(i,i,0), radius, color, 5);
            fb.draw(sb);
        }
        usleep(500000);
    }

    void drawMultiChoppedLine() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        Line line(Point(0,0,0), Point(500, 500, 0));

        float * radius = new float[5];
        radius[0] = 0;
        radius[1] = 100;
        radius[2] = 200;
        radius[3] = 300;
        radius[4] = 400;

        Color * color = new Color[5];
        color[0] = Color(255, 0, 0);
        color[1] = Color(0, 255, 0);
        color[2] = Color(0, 0, 255);
        color[3] = Color(255, 0, 255);
        color[4] = Color(128, 255, 0);

        for (int i = 0; i < 500; i+=20) {
            sb.clear();
            line.drawChopped(sb, Point(i,i,0), radius, color, 5, 20);
            fb.draw(sb);
        }
        usleep(500000);
    }
};

#endif