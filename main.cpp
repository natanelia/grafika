#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"
#include "Line.h"

#include "test.cpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int performTests() {
    Test test;
    test.testShapeGroup();
    test.testShape();
    test.testLine();
    test.testImage();
    test.testRedraw();
}

int main() {
    srand(time(NULL));

    performTests();

    return 0;
}