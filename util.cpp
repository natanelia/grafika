#ifndef __UTIL
#define __UTIL

#include "Point.h"
#include "Image.h"
#include "ColorTable.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>

using namespace std;

class Util {
public:
    static Image& convertImageFile(string fileName, ColorTable& ct) {
        ifstream file(fileName.c_str());
        string str;
        int x, y, z;
        vector<Point> * points = new vector<Point>();
        vector<Color> * colors = new vector<Color>();

        y = 0; z = 0;
        while (getline(file, str))
        {
            x = 0;
            for (int i = 0; i < str.length() - 1; ++i) {
                if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r') {
                    points->push_back(Point(x, y, z, 0));
                    colors->push_back(ct.getColor(str[i]));
                }
                ++x;
            }
            ++y;
        }

        file.close();


        Image * img = new Image(*points, *colors);
        return *img;
    }

    static vector<vector<Point> > convertPoint(map<string, vector<Point> > object, string word, int a, int b, int c, float x, float y, float z) {
        Point p;

        vector<vector<Point> > image;
        vector<Point> points = object.find(word)->second;
        vector<Point> component;
        for (int j = 0; j < points.size(); j++) {
            while (!(points[j].x == -1000 && points[j].y == -1000 && points[j].z == -1000) && j < points.size()) {
                p.x = a + points[j].x * x;
                p.y = b + points[j].y * y;
                p.z = c + points[j].z * z;
                component.push_back(p);

                j++;
            }
            component.pop_back();
            p.x = points[j - 1].x;
            p.y = points[j - 1].y;
            p.z = points[j - 1].z;
            component.push_back(p);

            image.push_back(component);
            component.clear();
        }

        return image;
    }

    static map<string, vector<Point> > readObject(string fileName) {
        ifstream file(fileName.c_str());
        string str;
        map<string, vector<Point> > objects;
        while(getline(file,str)) {
            string key = "";

            //ambil key
            int j=0;
            while(str[j]!=' ') {
                key+=str[j];
                j++;
            }

            vector<Point> points;
            int i = j;
            while(str[i]!=';') {
                if(str[i]!=' ') {
                    Point point;

                    //Ambil x
                    string temp = "";
                    while(str[i]!=',') {
                        temp += str[i];
                        i++;
                    }

                    int x = atoi(temp.c_str());
                    //Ambil y
                    i++;
                    temp = "";
                    while(str[i]!=',') {
                        temp += str[i];
                        i++;
                    }
                    int y = atoi(temp.c_str());

                    //Ambil z
                    i++;
                    temp = "";
                    while(str[i]!=',') {
                        temp += str[i];
                        i++;
                    }
                    int z = atoi(temp.c_str());

                    
                    //Ambil tag
                    i++;
                    temp = "";
                    while(str[i]!=' ' && str[i]!=';') {
                        temp += str[i];
                        i++;
                    }
                    int tag = atoi(temp.c_str());

                    //Isi point
                    point.x = x;
                    point.y = y;
                    point.z = z;
                    point.tag = tag;

                    points.push_back(point);
                } else {
                    i++;
                }

            }
            objects[key] = points;
        }

        file.close();
        return objects;
    }

    /*static map<string, vector<Point> > readObject(string fileName) {
        ifstream file(fileName.c_str());
        string str;
        map<string, vector<Point> > objects;
        while(getline(file,str)) {

            string key = "";

            //ambil key
            int j=0;
            while(str[j]!=' ') {
                key+=str[j];
                j++;
            }

            vector<Point> points;
            int i = j;
            while(str[i]!=';') {
                if(str[i]!=' ') {
                    Point point;

                    //Ambil x
                    string temp = "";
                    while(str[i]!=',') {
                        temp += str[i];
                        i++;
                    }

                    int x = atoi(temp.c_str());
                    //Ambil y
                    i++;
                    temp = "";
                    while(str[i]!=',') {
                        temp += str[i];
                        i++;
                    }
                    int y = atoi(temp.c_str());

                    
                    //Ambil z
                    i++;
                    temp = "";
                    while(str[i]!=' ' && str[i]!=';') {
                        temp += str[i];
                        i++;
                    }
                    int z = atoi(temp.c_str());

                    //Isi point
                    point.x = x;
                    point.y = y;
                    point.z = z;

                    points.push_back(point);
                } else {
                    i++;
                }

            }
            objects[key] = points;
        }

        file.close();
        return objects;
    }*/
};

#endif