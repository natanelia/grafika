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
    void testLine() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        vector<Point> points;
        points.push_back(Point(0, 20));
        points.push_back(Point(800, 500));
        Line line(points);

        for (int i = 0; i < 360; i++) {
            Point * tipPoints = line.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            line.rotate(midAxis, 5);
            line.color = Color(rand() % 255, rand() % 255, rand() % 255);

            sb.clear();
            line.draw(sb);
            fb.draw(sb);
        }
    }

    void testShape() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        map<string, vector<Point> > point = util.readObject("point.txt");
        Shape shape(util.convertPoint(point, "Baling", 0, 0, 2, 2)[0]);

        for (int i = 0; i < 360; i++) {
            Point * tipPoints = shape.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            shape.rotate(midAxis, 5);
            shape.scale(midAxis, 1.005, 1.005);
            shape.color = Color(rand() % 255, rand() % 255, rand() % 255);

            sb.clear();
            shape.draw(sb);
            fb.draw(sb);
        }
    }

    void testShapeGroup() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);

        ShapeGroup helikopter("Helikopter");

        helikopter.translate(500, 500);

        for (int i = 0; i < 180; i++) {
            Point * tipPoints = helikopter.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            helikopter.rotate(midAxis, 5);
            helikopter.scale(midAxis, 1.005, 1.005);

            for (int i = 0; i < helikopter.shapes.size(); i++) {
                helikopter.shapes[i].color = Color(rand() % 255, rand() % 255, rand() % 255);
            }

            sb.clear();
            helikopter.draw(sb);
            fb.draw(sb);
        }
    }

    void testImage() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);

        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);
        Image ship(util.convertImageFile("assets/kapal.txt"));
        ship.translate(10, sb.height - 200);
        ship.color = Color(0, 0, 255);

        Image ship2(util.convertImageFile("assets/kapal.txt"));
        ship2.translate(10, sb.height - 200);
        ship2.color = Color(255, 0, 255);

        while (ship.points[0].y > -200) {
            ship.translate(5, -10);
            Point * tipPoints = ship.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            ship.rotate(midAxis, 5);
            ship.scale(midAxis, 1.02, 1.02);

            ship.color = Color(rand() % 255, rand() % 255, rand() % 25);

            ship2.translate(5, 10);
            Point * tipPoints2 = ship2.getTipPoints();
            Point midAxis2((tipPoints2[0].x + tipPoints2[1].x) / 2, (tipPoints2[0].y + tipPoints2[1].y) / 2);
            ship2.rotate(midAxis2, 5);
            ship2.scale(midAxis2, 0.98, 0.98);

            ship2.color = Color(rand() % 255, rand() % 255, rand() % 25);

            sb.clear();
            ship.draw(sb);
            ship2.draw(sb);
            fb.draw(sb);
        }

        while (ship.points[0].y < sb.height - 137) {
            ship.translate(5, 10);

            Point * tipPoints = ship.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            ship.rotate(midAxis, 5);

            ship.scale(midAxis, 0.98, 0.98);

            ship.color = Color(rand() % 255, rand() % 255, rand() % 25);


            ship2.translate(5, -10);

            Point * tipPoints2 = ship2.getTipPoints();
            Point midAxis2((tipPoints2[0].x + tipPoints2[1].x) / 2, (tipPoints2[0].y + tipPoints2[1].y) / 2);
            ship2.rotate(midAxis2, 5);

            ship2.scale(midAxis, 1.02, 1.02);

            ship2.color = Color(rand() % 255, rand() % 255, rand() % 25);

            sb.clear();
            ship.draw(sb);
            ship2.draw(sb);
            fb.draw(sb);
        }
    }


    void testRedraw() {
        FrameBuffer fb;
        fb.backgroundColor = (Color(255, 255, 255));
        fb.clear();

        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
        sb.backgroundColor = Color(50, 50, 50);

        ShadowBuffer sb2(sb.width - 100, sb.height, 0, 0, fb.finfo.line_length);
        sb2.backgroundColor = (Color(100, 100, 100));

        ShadowBuffer sb3(200, 200, 1166, 0, fb.finfo.line_length);
        sb3.backgroundColor = (Color(0, 0, 0));
        sb3.clear();

        sb.shadows.push_back(&sb2);
        sb.shadows.push_back(&sb3);

        for (int j = 0; j < 50; j++) {
            sb.clear();
            sb2.clear();

            //START create boxes
            for (int i = 0; i < 50; i++) {
                Color c(rand() % 255, rand() % 255, rand() % 255);
                int offsetX = rand() % sb2.width;
                int offsetY = rand() % sb2.height;
                for (int y = 0; y < 100; y++) {
                    for (int x = 0; x < 100; x++) {
                        sb2.plot(offsetX + x, offsetY + y, c);
                    }
                }
            }
            sb3.offsetX -= 2;
            sb3.offsetY += 4;
            //END create boxes

            sb.draw();
            fb.draw(sb);
        }
    }
};

#endif