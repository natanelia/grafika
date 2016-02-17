#ifndef __TEST

#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

class Test {
public:
    void testImage() {
        Util util;
        FrameBuffer fb;
        ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);

        fb.backgroundColor = Color(0, 20, 30);
        sb.backgroundColor = Color(0, 20, 30);
        Image ship(util.convertImageFile("assets/kapal.txt"));
        ship.translate(10, sb.height - 200);
        ship.color = Color(0, 0, 255);

        while (ship.points[0].y > -200) {
            ship.translate(5, -10);

            Point * tipPoints = ship.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            ship.rotate(midAxis, 5);

            ship.scale(midAxis, 1.02, 1.02);

            sb.clear();
            ship.draw(sb);
            fb.draw(sb);
        }

        while (ship.points[0].y < sb.height - 137) {
            ship.translate(5, 10);

            Point * tipPoints = ship.getTipPoints();
            Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
            ship.rotate(midAxis, 5);

            ship.scale(midAxis, 0.98, 0.98);

            sb.clear();
            ship.draw(sb);
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
            //END create boxes

            sb.draw();
            fb.draw(sb);
        }
    }
};

#endif