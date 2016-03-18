#ifndef __COLORTABLE
#define __COLORTABLE

#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include "Color.h"

class ColorTable {
private:
    std::map<char, Color> table;
public:
    ColorTable(std::string fileName);

    Color getColor(char code);
    Color getColor(char code, Color& hue);
};

#endif