#include "Drawing.h"

Drawing::Drawing(Point points[], int n) {
    for (int i = 0; i < n; i++) {
        this->points.push_back(points[i]);
    }
}

Drawing::Drawing(vector<Point>& points) {
    for (int i = 0; i < points.size(); i++) {
        this->points.push_back(points[i]);
    }
}

void Drawing::rotate(Point axis, float angle) {
    float angleRadian = angle * PI / 180.0;
    float s = sin(angleRadian);
    float c = cos(angleRadian);

    for (int i = 0 ; i < points.size() ; i++){
        points[i].x -= axis.x;
        points[i].y -= axis.y;

        float xnew = points[i].x * c  - points[i].y * s;
        float ynew = points[i].x * s  + points[i].y * c;

        // translate point back:
        points[i].x = xnew + axis.x;
        points[i].y = ynew + axis.y;
    }
}

void Drawing::translate(float dX, float dY) {
    for (int i = 0; i < points.size(); i++) {
        points[i].x += dX;
        points[i].y += dY;
    }
}

void Drawing::scale(Point axis, float scalingFactorX, float scalingFactorY) {
    //melakukan scaling pada titik2 vektor "v" berdasarkan poros "axis". Scaling dilakukan sebesar "scalingFactor"

    //Sumbu scaling
    float axisX = axis.x;
    float axisY = axis.y;

    for (int i = 0 ; i < points.size() ; i++){
        Point pResult;
        //jarak titik dengan sumbu

        float dX = abs((axisX-points[i].x)*scalingFactorX);
        float dY = abs((axisY-points[i].y)*scalingFactorY);

        //Melakukan scaling berdasarkan
        if (points[i].x > axisX && points[i].y<axisY) {//Kuadran 1
            points[i].x = axisX + dX;
            points[i].y = axisY - dY;
            //printf("%4.2f", pResult.x);
            //printf("%4.2f", pResult.y);
        } else if (points[i].x < axisX && points[i].y<axisY) { //kuadran 2
            points[i].x = axisX - dX;
            points[i].y =  axisY - dY;
        } else if (points[i].x < axisX && points[i].y>axisY) { //kuadran 3
            points[i].x = axisX - dX;
            points[i].y =  axisY + dY;
        } else if (points[i].x > axisX && points[i].y>axisY) { //kuadran 4
            points[i].x = axisX + dX;
            points[i].y =  axisY + dY;
        } else if (points[i].x == axisX && points[i].y == axisY){ //titik itu sendiri
            points[i].x = axisX;
            points[i].y = axisY;
        } else if (points[i].x == axisX) {//sumbu X
            points[i].x = axisX;
            if (points[i].y>axisY){
                points[i].y =  axisY + dY;
            } else{
                points[i].y =  axisY - dY;
            }
        } else if (points[i].y == axisY) {//sumbu Y
            points[i].y = axisY;
            if (points[i].x>axisX){
                points[i].x =  axisX + dY;
            } else{
                points[i].x =  axisX - dX;
            }
        }
    }
}

Point * Drawing::getTipPoints() {
    Point * p = new Point[2];

    p[0] = Point(points.at(0).x, points.at(0).y, points.at(0).z);
    p[1] = Point(points.at(0).x, points.at(0).y, points.at(0).z);

    for (int i = 1; i < points.size(); i++) {
        if (p[0].x > points[i].x) {
            p[0].x = points[i].x;
        }
        if (p[0].y > points[i].y) {
            p[0].y = points[i].y;
        }
        if (p[1].x < points[i].x) {
            p[1].x = points[i].x;
        }
        if (p[1].y < points[i].y) {
            p[1].y = points[i].y;
        }
    }

    return p; //first p means top left, second means bottom right
}

void Drawing::clip(Point min, Point max, float scale) {
    ClippingHelper Clipper;

    clippedPoints.clear();

    vector<int> tag;

    for (int i = 0; i < points.size(); i++)
    {
        Point A;
        Point B;
        if (i != points.size() - 1) {
            A = points[i];
            B = points[i+1];
        } else {
            A = points[i];
            B = points[0];
        }

        if (Clipper.getBinaryCode(A,min,max) == 0) {
            clippedPoints.push_back(A);
            tag.push_back(0);
            if (Clipper.getBinaryCode(B,min,max) != 0) {
                Point* intersectionPoints = Clipper.getIntersection(A,B,min,max);
                clippedPoints.push_back(intersectionPoints[0]);
                tag.push_back(0);
                clippedPoints.push_back(intersectionPoints[1]);
                tag.push_back(0);
            }
        } else {
            clippedPoints.push_back(A);
            tag.push_back(1);
            if (Clipper.andBinary(Clipper.getBinaryCode(A,min,max),Clipper.getBinaryCode(B,min,max)) == 0) {
                Point* intersectionPoints = Clipper.getIntersection(A,B,min,max);
                clippedPoints.push_back(intersectionPoints[0]);
                tag.push_back(0);
                clippedPoints.push_back(intersectionPoints[1]);
                tag.push_back(0);
            }
            
        }
    }
   
    for(int i = 0; i < tag.size(); i++){
        if (tag[i] == 1) {
            clippedPoints[i] = Clipper.findNearestPoint(clippedPoints[i], min, max);
            tag[i] = 0;
        } 
    }

    for (int i = 0; i < clippedPoints.size(); i++) {
        int j = i + 1;
        int k = i + 2;

        if (i == clippedPoints.size() - 2) {
            k = 0;
        } else if (i == clippedPoints.size() - 1) {
            j = 0;
            k = 1;
        }
        if((clippedPoints[i].x == clippedPoints[j].x) && (clippedPoints[i].y == clippedPoints[j].y)){
            clippedPoints.erase(clippedPoints.begin()+j);
            i--;
        }

        else if (((clippedPoints[i].x == clippedPoints[j].x) && (clippedPoints[i].x == clippedPoints[k].x)) || ((clippedPoints[i].y == clippedPoints[j].y) && (clippedPoints[i].y == clippedPoints[k].y))) {
            clippedPoints.erase(clippedPoints.begin()+j);
            i--;
        }
    }

    for (int i = 0; i < clippedPoints.size(); i++){
        clippedPoints[i].x -= min.x;
        clippedPoints[i].y -= min.y;
        clippedPoints[i].x *= scale;
        clippedPoints[i].y *= scale;
    }
}