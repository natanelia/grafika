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

    // for (int i = 0 ; i < points.size() ; i++){
    //     points[i].x += axis.x;
    //     points[i].y +=  axis.y;
    //      points[i].x *= scalingFactorX;
    //     points[i].y *=  scalingFactorY;
    //     points[i].x -= axis.x;
    //     points[i].y -=  axis.y;
    // }

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

int Drawing::andBinary (int code1, int code2) {
    int hasil = 0;

    if ((code1 % 10 == 1) && (code2 % 10 == 1))
        hasil++;
    if ((((code1 % 100)/10) == 1) && (((code2 %100)/10) == 1))
        hasil += 10;
    if ((((code1 % 1000)/100) == 1) && (((code2 % 1000)/100) == 1))
        hasil += 100;
    if ((code1 / 1000 == 1) && (code2 / 1000 == 1))
        hasil += 1000;

    return hasil;
}

int Drawing::getBinaryCode(Point P, Point min, Point max) {
    int result = 0;

    if (P.y < min.y)
        result += 1000;
    else if (P.y > max.y)
        result += 100;
    
    if (P.x < min.x)
        result += 1;
    else if (P.x > max.x)
        result += 10;
    return result;
}

Point* Drawing::getIntersection(Point P, Point Q, Point min, Point max) {
    Point* results = new Point[2];

    //cout<<"A. P: "<<P.x<<","<<P.y<<" Q: "<<Q.x<<","<<Q.y<<" min: "<<min.x<<","<<min.y<<" max: "<<max.x<<","<<max.y<<endl;
    if (P.y < min.y) {
        P.x = P.x + (min.y - P.y) * (Q.x - P.x) / (Q.y - P.y);
        P.y = min.y;
    } else if (P.y > max.y) {
        P.x = P.x + (P.y - max.y) * (Q.x - P.x) / (P.y - Q.y);
        P.y = max.y;
    }
    //cout<<"B. P: "<<P.x<<","<<P.y<<" Q: "<<Q.x<<","<<Q.y<<" min: "<<min.x<<","<<min.y<<" max: "<<max.x<<","<<max.y<<endl;
    if (P.x < min.x) {
        P.y = P.y + (min.x - P.x) * (Q.y - P.y) / (Q.x - P.x);
        P.x = min.x;
    } else if (P.x > max.x) {
        P.y = P.y + (P.x - max.x) * (Q.y - P.y) / (P.x - Q.x);
        P.x = max.x;
    }

    if (P.y < min.y){
        P.y = min.y;
    } else if (P.y > max.y){
        P.y = max.y;
    }

    //cout<<"C. P: "<<P.x<<","<<P.y<<" Q: "<<Q.x<<","<<Q.y<<" min: "<<min.x<<","<<min.y<<" max: "<<max.x<<","<<max.y<<endl;
    if (Q.y < min.y) {
        Q.x = Q.x + (min.y - Q.y) * (P.x - Q.x) / (P.y - Q.y);
        Q.y = min.y;
    } else if (Q.y > max.y) {
        Q.x = Q.x + (Q.y - max.y) * (P.x - Q.x) / (Q.y - P.y);
        Q.y = max.y;
    }
    //cout<<"D. P: "<<P.x<<","<<P.y<<" Q: "<<Q.x<<","<<Q.y<<" min: "<<min.x<<","<<min.y<<" max: "<<max.x<<","<<max.y<<endl;
    if (Q.x < min.x) {
        Q.y = Q.y + (min.x - Q.x) * (P.y - Q.y) / (P.x - Q.x);
        Q.x = min.x;
    } else if (Q.x > max.x) {
        Q.y = Q.y + (Q.x - max.x) * (P.y - Q.y) / (Q.x - P.x);
        Q.x = max.x;
    }

    if (Q.y < min.y){
        Q.y = min.y;
    } else if (Q.y > max.y){
        Q.y = max.y;
    }
    //cout<<"E. P: "<<P.x<<","<<P.y<<" Q: "<<Q.x<<","<<Q.y<<" min: "<<min.x<<","<<min.y<<" max: "<<max.x<<","<<max.y<<endl;
    results[0] = P;
    results[1] = Q;
    
    return results;
}

Point Drawing::findNearestPoint(Point P, Point min, Point max) {
    Point hasil;

    if (abs(min.x - P.x) < abs(max.x - P.x)) {
        hasil.x = min.x;
    } else {
        hasil.x = max.x;
    }

    if (abs(min.y - P.y) < abs(max.y - P.y)) {
        hasil.y = min.y;
    } else {
        hasil.y = max.y;
    }

    return hasil;
}

void Drawing::clip(Point min, Point max, float scale) {
    clippedPoint.clear();

    vector<int> tag;


    /*cout<<"BEFORE";
    for(int i = 0; i < points.size(); i++){
        cout<<points[i].x<<","<<points[i].y<<" ";
    }
    cout<<endl;*/

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

        if (getBinaryCode(A,min,max) == 0) {
            //cout<<"1. P: "<<A.x<<","<<A.y<<" Q: "<<B.x<<","<<B.y<<endl;
            clippedPoint.push_back(A);
            tag.push_back(0);
            if (getBinaryCode(B,min,max) != 0) {
                //cout<<"2. P: "<<A.x<<","<<A.y<<" Q: "<<B.x<<","<<B.y<<endl;
                Point* intersectionPoints = getIntersection(A,B,min,max);
                clippedPoint.push_back(intersectionPoints[0]);
                tag.push_back(0);
                clippedPoint.push_back(intersectionPoints[1]);
                tag.push_back(0);
                //cout<<"2. P: "<<intersectionPoints[0].x<<","<<intersectionPoints[0].y<<" Q: "<<intersectionPoints[1].x<<","<<intersectionPoints[1].y<<endl;
            }
        } else {
            //cout<<"3. P: "<<A.x<<","<<A.y<<" Q: "<<B.x<<","<<B.y<<endl;
            clippedPoint.push_back(A);
            tag.push_back(1);
            if (andBinary(getBinaryCode(A,min,max),getBinaryCode(B,min,max)) == 0) {
                //cout<<"4. P: "<<A.x<<","<<A.y<<" Q: "<<B.x<<","<<B.y<<endl;
                Point* intersectionPoints = getIntersection(A,B,min,max);
                clippedPoint.push_back(intersectionPoints[0]);
                tag.push_back(0);
                clippedPoint.push_back(intersectionPoints[1]);
                tag.push_back(0);
                //cout<<"4. P: "<<intersectionPoints[0].x<<","<<intersectionPoints[0].y<<" Q: "<<intersectionPoints[1].x<<","<<intersectionPoints[1].y<<endl;
            }
            
        }
    }
    /*cout<<"AA ";
    for(int i = 0; i <clippedPoint.size(); i++){
        cout<<clippedPoint[i].x<<","<<clippedPoint[i].y<<" ";
    }
    cout<<endl;
    cout<<"BB ";
    for(int i = 0; i <clippedPoint.size(); i++){
        cout<<tag[i]<<" ";
    }
    cout<<endl;*/
   
    for(int i = 0; i < tag.size(); i++){
        if (tag[i] == 1) {
            clippedPoint[i] = findNearestPoint(clippedPoint[i], min, max);
            tag[i] = 0;
        } 
    }


    /*cout<<"CC ";
    for(int i = 0; i <clippedPoint.size(); i++){
        cout<<clippedPoint[i].x<<","<<clippedPoint[i].y<<" ";
    }
    cout<<endl;
    cout<<"DD ";
    for(int i = 0; i <clippedPoint.size(); i++){
        cout<<tag[i]<<" ";
    }
    cout<<endl;*/
    
    for (int i = 0; i < clippedPoint.size(); i++) {
        int j = i + 1;
        int k = i + 2;

        if (i == clippedPoint.size() - 2) {
            k = 0;
        } else if (i == clippedPoint.size() - 1) {
            j = 0;
            k = 1;
        }
        if((clippedPoint[i].x == clippedPoint[j].x) && (clippedPoint[i].y == clippedPoint[j].y)){
            clippedPoint.erase(clippedPoint.begin()+j);
            i--;
        }

        else if (((clippedPoint[i].x == clippedPoint[j].x) && (clippedPoint[i].x == clippedPoint[k].x)) || ((clippedPoint[i].y == clippedPoint[j].y) && (clippedPoint[i].y == clippedPoint[k].y))) {
            clippedPoint.erase(clippedPoint.begin()+j);
            i--;
        }
    }

    for (int i = 0; i < clippedPoint.size(); i++){
        clippedPoint[i].x -= min.x;
        clippedPoint[i].y -= min.y;
        clippedPoint[i].x *= scale;
        clippedPoint[i].y *= scale;
    }

    /*cout<<"CLIPPED";
    for(int i = 0; i <clippedPoint.size(); i++){
        cout<<clippedPoint[i].x<<","<<clippedPoint[i].y<<" ";
    }
    cout<<endl;*/
}