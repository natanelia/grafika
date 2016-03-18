#include "ColorTable.h"

ColorTable::ColorTable(std::string fileName) {
    std::string tmpString;

    std::ifstream txtFile(fileName.c_str());
    if (txtFile.is_open())
    {
        int i = 0;

        while (txtFile.good()) {
            getline(txtFile, tmpString);
            table[tmpString[0]] = Color(tmpString.substr(2, 6));
        }
        txtFile.close();
    }
}

Color ColorTable::getColor(char code) {
    return table[code];
}

Color ColorTable::getColor(char code, Color& hue) {
    Color c = table[code];
    c.r += hue.r % 255;
    c.g += hue.g % 255;
    c.b += hue.b % 255;

    return c;
}