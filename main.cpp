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
    //Test test;
    //test.drawLine();

    Util util;
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(0, 0, 0);
    sb.backgroundColor = Color(0, 0, 0);

    string filename = argv[1];
    //map<string, vector<Point> > point = util.readObject("assets/"+filename+".txt");
    //a.build3D(100);
    
    //a.translate(500,0,0);
    //a.draw(sb,100,100);
    // while(true){
      //sb.clear();
    //a.rotateX(90,0,0,0);
    //a.rotateX(90,0,0,0);
    // for (int i = 0; i < a.shapes.size(); i++) {
    //   for (int j = 0; j < a.shapes[i].points.size(); j++) {
    //     cout << a.shapes[i].points[j].x << "," << a.shapes[i].points[j].y << "," << a.shapes[i].points[j].z << endl;  
    //     // cout << "2d" << a.pointToPrint[i][j].x << "," << a.pointToPrint[i][j].y << endl;
    //   }
    //   cout << endl;
    // }

    int screenMiddleX = fb.vinfo.xres / 2;
    int screenMiddleY = fb.vinfo.yres / 2;
    
    ShapeGroup a("TigaPuluhSembilan", screenMiddleX, screenMiddleY, 1);
    a.draw(sb, screenMiddleX, screenMiddleY);
    fb.draw(sb);

    int c=0;
    //initTermios(0);

    int quit = 0;

    Point * groundTipPoints = a.getGroundTipPoints();

    while(!quit){

      c=getch();
      //resetTermios();
      switch(c){
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
        case '=':
          quit = 1;
        case 'u':
            a.translate(0,-10,0);
          break;
        case 'j':
            a.translate(0,10,0);
          break;
        case 'h':
            a.translate(-10,0,0);
          break;
        case 'k':
            a.translate(10,0,0);
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
      a.draw(sb,fb.vinfo.xres / 2,fb.vinfo.yres / 2);
      fb.draw(sb);
    }
    delete [] groundTipPoints;
    resetTermios();
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
