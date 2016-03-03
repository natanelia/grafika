#ifndef __UTIL
#define __UTIL

#include "Point.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>

using namespace std;

class Util {
public:
    static vector<Point>& convertImageFile(string fileName) {
        ifstream file(fileName.c_str());
        string str;
        int x, y, z;
        vector<Point> * points = new vector<Point>();

        y = 0; z = 0;
        while (getline(file, str))
        {
            x = 0;
            for (int i = 0; i < str.length() - 1; ++i) {
                if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r') {
                    points->push_back(Point(x,y,z));
                }
                ++x;
            }
            ++y;
        }

        file.close();
        return *points;
    }

    static vector<vector<Point> > convertPoint(map<string, vector<Point> > object, string word, int a, int b, int c, int x, int y, int z) {
        Point p;

        vector<vector<Point> > image;
        vector<Point> points = object.find(word)->second;
        vector<Point> component;
        for (int j = 0; j < points.size(); j++){
            if (points[j].x == -1000 && points[j].y == -1000 && points[j].z == -1000) {
                image.push_back(component);
                component.clear();
            } else {
                p.x = a + points[j].x * x;
                p.y = b + points[j].y * y;
                p.z = c + points[j].z * z;
                component.push_back(p);
            }
        }
        image.push_back(component);

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
    }
};

#endif