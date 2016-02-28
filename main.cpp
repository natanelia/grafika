#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"
#include "Line.h"
#include "Shape.h"
#include "ShapeGroup.h"
#include <termios.h>
#include <unistd.h>

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
    FrameBuffer fb;
    ShadowBuffer sb(fb.width, fb.height, 0, 0, fb.finfo.line_length);
    fb.backgroundColor = Color(0, 20, 30);
    sb.backgroundColor = Color(0, 20, 30);

    ShapeGroup Logothesims("Diamond");
    sb.clear();
    Logothesims.draw(sb);
    fb.draw(sb);


    return 0;
}
