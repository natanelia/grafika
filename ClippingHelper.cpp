#include "ClippingHelper.h"

int ClippingHelper::andBinary (int code1, int code2) {
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

int ClippingHelper::getBinaryCode(Point P, Point min, Point max) {
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

Point* ClippingHelper::getIntersection(Point P, Point Q, Point min, Point max) {
    Point* results = new Point[2];

    if (P.y < min.y) {
        P.x = P.x + (min.y - P.y) * (Q.x - P.x) / (Q.y - P.y);
        P.y = min.y;
    } else if (P.y > max.y) {
        P.x = P.x + (P.y - max.y) * (Q.x - P.x) / (P.y - Q.y);
        P.y = max.y;
    }

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

    if (Q.y < min.y) {
        Q.x = Q.x + (min.y - Q.y) * (P.x - Q.x) / (P.y - Q.y);
        Q.y = min.y;
    } else if (Q.y > max.y) {
        Q.x = Q.x + (Q.y - max.y) * (P.x - Q.x) / (Q.y - P.y);
        Q.y = max.y;
    }

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

    results[0] = P;
    results[1] = Q;
    
    return results;
}

Point ClippingHelper::findNearestPoint(Point P, Point min, Point max) {
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