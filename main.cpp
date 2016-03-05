#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"
#include "Line.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include "test.cpp"
#include <termios.h>
#include <unistd.h>
#include "Face.h"

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
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
    Test test;
    test.drawMultiChoppedLine();

    Util util;
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(255, 255, 255);
    sb.backgroundColor = Color(255, 255, 255);

    string filename = argv[1];
    map<string, vector<Point> > point = util.readObject("assets/"+filename+".txt");
 
    Face face(point,100,100,0,10);
    int i = 0;
    //while(true){
      // fb.clear();
      // face.eyes.wink(RIGHT);
      // face.smile();
      // face.draw(sb);
      // fb.draw(sb);
      // i++;
    while(true){
      sb.clear();
      face.eyes.closeEyes();
      face.smile();
      face.draw(sb);
      fb.draw(sb);
      usleep(1000000);
      sb.clear();
      face.eyes.normal();
      face.openMouth();
      face.draw(sb);
      fb.draw(sb);
      usleep(1000000);
    }
    
    /*
    int offSetX = 670;
    int offSetY = 350;

    ShapeGroup Logothesims("Diamond6",offSetX,offSetY,70);
    int position = 0;
    int translation = 2;
    //Logothesims.rotateX(5,offSetX, offSetY,0);

    vector<Point> points = util.convertImageFile("assets/logo.txt");
    Image logo(points);
    logo.color = Color(0, 0, 255);
    logo.translate(550,100);

    Image logoShadow(points);
    logoShadow.color = Color(220, 220, 220);
    logoShadow.translate(550,110);


    while(true){
      if (position > 20){
        translation *= -1;
      }
      if (position < -20){
        translation *= -1;
      }
      Logothesims.translate(0,translation,0);
      position += translation;
      Logothesims.rotateY(3,offSetX,offSetY,0);

      logo.translate(0, -translation / 2);
      logoShadow.translate(0, -translation / 2);

      sb.clear();
      logoShadow.draw(sb);
      logo.draw(sb);
      Logothesims.draw(sb,offSetX,offSetY);

      fb.draw(sb);
      usleep(5000);
	}
*/
    return 0;
}
