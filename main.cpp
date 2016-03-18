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
#include "ColorTable.h"

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
    Util util;
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(255, 255, 255);
    sb.backgroundColor = Color(255, 255, 255);
    float offsetX = 100;
    float offsetY = 100;

    string filename = argv[1];
    //map<string, vector<Point> > point = util.readObject("assets/"+filename+".txt");
    ShapeGroup a("Dua",offsetX,offsetY,5);
    a.build3D(20);
    
    //a.translate(500,0,0);
    //a.draw(sb,100,100);
    // while(true){
      //sb.clear();
    //a.rotateX(90,off,0,0);
    // for (int i = 0; i < a.shapes.size(); i++) {
    //   for (int j = 0; j < a.shapes[i].points.size(); j++) {
    //     cout << a.shapes[i].points[j].x << "," << a.shapes[i].points[j].y << "," << a.shapes[i].points[j].z << endl;  
    //     // cout << "2d" << a.pointToPrint[i][j].x << "," << a.pointToPrint[i][j].y << endl;
    //   }
    //   cout << endl;
    // }
      a.draw(sb,offsetX,offsetY);
      fb.draw(sb);
      // usleep(1000000);
    // }
  
    /*for (int i = 0; i < a.shapes.size(); i++) {
      for (int j = 0; j < a.shapes[i].points.size(); j++) {
        cout << a.shapes[i].points[j].x << "," << a.shapes[i].points[j].y << "," << a.shapes[i].points[j].z << endl;  
      }
      cout << endl;
    }*/
  
    //usleep(1000000);
    
    
    /*int offSetX = 670;
    int offSetY = 350;

    cout << "WOI" << endl;
    ShapeGroup Logothesims("Diamond6",offSetX,offSetY,70);
    int position = 0;
    int translation = 2;
    //Logothesims.rotateX(5,offSetX, offSetY,0);

    cout << "TEST" << endl;
    ColorTable ct("assets/ColorTable.ct");

    // Image logo = util.convertImageFile("assets/logo.txt", ct);
    // logo.translate(550,100);

    // Image logoShadow = util.convertImageFile("assets/logo.txt", ct);
    // logoShadow.translate(550,110);

    while(true){
      cout<<"RYAN"<<endl;
      if (position > 20){
        translation *= -1;
      }
      if (position < -20){
        translation *= -1;
      }
      Logothesims.translate(0,translation,0);
      position += translation;
      Logothesims.rotateY(3,offSetX,offSetY,0);

      // logo.translate(0, -translation / 2);
      // logoShadow.translate(0, -translation / 2);

      sb.clear();
      // logoShadow.draw(sb);
      // logo.draw(sb);
      Logothesims.draw(sb,offSetX,offSetY);

      fb.draw(sb);
	  }*/

    return 0;
}
