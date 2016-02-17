#include "FrameBuffer.h"
#include "ShadowBuffer.h"
#include "util.cpp"
#include "Image.h"

#include "test.cpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int performTests() {
    Test test;
    test.testRedraw();
    test.testImage();
}

int main() {
    srand(time(NULL));

    performTests();

    return 0;
}