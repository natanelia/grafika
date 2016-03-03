#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "test.cpp"
#include "Image.h"
#include "Line.h"
#include <termios.h>
#include <unistd.h>

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

int performTests() {
    Test test;
    //test.testRedraw();
    test.testShapeGroup();

    //test.testShape();
   /* test.testLine();
    test.testImage();*/
}

int main(int argc, char *argv[]) {
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(0, 20, 30);
    sb.backgroundColor = Color(0, 20, 30);

    ShapeGroup indonesia("Sumatra");
    ShapeGroup indonesia1("Kalimantan");
    sb.clear();
    indonesia.draw(sb);
    indonesia1.draw(sb);
    fb.draw(sb);
	// FrameBuffer fb;
 //    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
 //    fb.backgroundColor = Color(0, 20, 30);
 //    sb.backgroundColor = Color(0, 20, 30);

	// vector<Point> points2;
 //    Point p5(0, 0);
 //    Point p6(0.25* (fb.vinfo.xres), 0);
 //    Point p7(0.25* (fb.vinfo.xres), 0.25* (fb.vinfo.yres));
 //    Point p8(0, 0.25*(fb.vinfo.yres));
 //    points2.push_back(p5);
	// points2.push_back(p6);
	// points2.push_back(p7);
	// points2.push_back(p8);

	// Shape minimap(points2);
	
	

	// minimap.color = Color(225,225,225);
	// minimap.translate(0.7* (fb.vinfo.xres), 0.7*(fb.vinfo.yres));

 //    ShapeGroup indonesia("Sumatra");

    
 //    Point * tipPoints = indonesia.getTipPoints();
 //    Point midAxis((tipPoints[0].x + tipPoints[1].x) / 2, (tipPoints[0].y + tipPoints[1].y) / 2);
    // for (int i = 0; i < indonesia.shapes.size(); i++) {
    //             indonesia.shapes[i].color = Color(rand() % 255, rand() % 255, rand() % 255);
    // }
     // indonesia.scale(midAxis, 0.45, 0.45);


    //Point * tipPoints2 = indonesia.getTipPoints();
    //indonesia.translate(minimap.points[0].x-tipPoints2[0].x, minimap.points[0].y-tipPoints2[0].y);
    


	// vector<Point> points;
	// points.push_back(minimap.points[0]);
	// points.push_back(minimap.points[1]);
	// points.push_back(minimap.points[2]);
	// points.push_back(minimap.points[3]);

	// Shape target(points);
	// target.scale(Point((minimap.points[1].x+minimap.points[0].x)/2,(minimap.points[1].y+minimap.points[2].y)/2),0.2,0.2);

	// Color C(225,0,0);
	
	// float scale = 19;
	// sb.clear();
	// indonesia.clip(target.points[0],target.points[2],19);
	// indonesia.drawClipped(sb);
	//minimap.draw(sb);
	// indonesia.draw(sb);
	//target.drawBorder(C,sb);
	// fb.draw(sb);

 //    int c=0;
 //    initTermios(0);

 //    while(1){

    	
 //    	c=getch();

 //    	resetTermios();
 //    	switch(c){
 //    		case 'a':
 //    			if(target.points[0].x > minimap.points[0].x)
 //    				target.translate(-5,0);
 //    			break;
 //    		case 's':
 //    			if(target.points[3].y < minimap.points[3].y)
 //    				target.translate(0,5);
 //    			break;
 //    		case 'd':
 //    			if(target.points[1].x < minimap.points[1].x)
 //    				target.translate(5,0);
 //    			break;
 //    		case 'w':
 //    			if(target.points[0].y > minimap.points[0].y)
 //    				target.translate(0,-5);
 //    			break;
 //    		case ',':
 //    			if((target.points[1].x-target.points[0].x >=8) && (target.points[2].y-target.points[1].y >=8)){
 //    				target.scale(Point((target.points[1].x+target.points[0].x)/2,(target.points[1].y+target.points[2].y)/2),0.995,0.995);
 //    				scale /= 0.995;
 //    			}
    		
 //    			break;
 //    		case '.':
 //    			if((target.points[0].x > minimap.points[0].x) && (target.points[3].y < minimap.points[3].y) && (target.points[1].x < minimap.points[1].x) && (target.points[0].y > minimap.points[0].y)){
 //    				target.scale(Point((target.points[1].x+target.points[0].x)/2,(target.points[1].y+target.points[2].y)/2),1.005,1.005);
 //    				scale /= 1.005;
 //    			}	
    			

 //    			break;
 //    	}
 //    	//initTermios();
 //    	sb.clear();
	// 	indonesia.clip(target.points[0],target.points[2],scale);
	// 	indonesia.drawClipped(sb);
 //    	minimap.draw(sb);
 //    	indonesia.draw(sb);
 //    	target.drawBorder(C,sb);
    	
 //    	fb.draw(sb);
    	

 //    }
	// srand(time(NULL));
	// //performTests();

 //    resetTermios();



    return 0;
}
