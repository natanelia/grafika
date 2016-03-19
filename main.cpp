#include "ColorTable.h"
#include "FrameBuffer.h"
#include "Image.h"
#include "ShadowBuffer.h"
#include "ShapeGroup.h"
#include "util.cpp"

#include <termios.h>
#include <iostream>

using namespace std;
static struct termios oldT, newT;
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &oldT); /* grab oldT terminal i/o settings */
  newT = oldT; /* make new settings same as oldT settings */
  newT.c_lflag &= ~ICANON; /* disable buffered i/o */
  newT.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &newT); /* use these new terminal i/o settings now */
}

/* Restore oldT terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &oldT);
}

char getch_(int echo) {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

char getch(void) {
	return getch_(0);	
}

char getche(void) {
	return getch_(1);	
}


int main(int argc, char *argv[]) {    
    Util util;
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(0, 128, 255);
    sb.backgroundColor = Color(0, 128, 255);

    string filename;
    if (argc > 1) {
      filename = argv[1];
    } else {
      filename = "default";
    }

    int height;
    if (argc > 2) {
      height = atoi(argv[2]);
    } else {
      height = 50;
    }

    int screenMiddleX = fb.vinfo.xres / 2;
    int screenMiddleY = fb.vinfo.yres / 2;
    
    ShapeGroup a(filename, screenMiddleX, screenMiddleY, 3);
    Point lightSource(screenMiddleX, screenMiddleY, height * 1.2f);
    a.build3D(height, lightSource, height * 20);

    sb.clear();
    a.draw(sb, screenMiddleX, screenMiddleY);
    fb.draw(sb);

    int c = 0;

    Point * groundTipPoints = a.getGroundTipPoints();

    while (c != '=') {
      c = getch();

      switch(c) {
        case 'a':
            a.rotateY(-2, (groundTipPoints[0].x + groundTipPoints[1].x) / 2, (groundTipPoints[0].y + groundTipPoints[1].y) / 2, groundTipPoints[0].z);
          break;
        case 's':
            a.rotateX(-10, (groundTipPoints[0].x + groundTipPoints[1].x) / 2, (groundTipPoints[0].y + groundTipPoints[1].y) / 2, groundTipPoints[0].z);
          break;
        case 'd':
            a.rotateY(2, (groundTipPoints[0].x + groundTipPoints[1].x) / 2, (groundTipPoints[0].y + groundTipPoints[1].y) / 2, groundTipPoints[0].z);
          break;
        case 'w':
            a.rotateX(10, (groundTipPoints[0].x + groundTipPoints[1].x) / 2, (groundTipPoints[0].y + groundTipPoints[1].y) / 2, groundTipPoints[0].z);
          break;
        case 'u':
            a.translate(0,-10,0);
            groundTipPoints[0].translation(0,-10,0);
          break;
        case 'j':
            a.translate(0,10,0);
            groundTipPoints[0].translation(0,10,0);
          break;
        case 'h':
            a.translate(-10,0,0);
            groundTipPoints[0].translation(-10,0,0);
          break;
        case 'k':
            a.translate(10,0,0);
            groundTipPoints[0].translation(10,0,0);
          break;
        case 'i':
            a.translate(0,0,-10);
            groundTipPoints[0].translation(0,0,-10);
          break;
        case 'n':
            a.translate(0,0,10);
            groundTipPoints[0].translation(0,0,10);
          break;
      }
      sb.clear();
      a.draw(sb, screenMiddleX, screenMiddleY);
      fb.draw(sb);
    }

    delete [] groundTipPoints;

    return 0;
}
