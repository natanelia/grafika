#include "Line.h"

Line::Line(vector<Point>& points) : Drawing(points) {}

Line::Line(Point points[], int n) : Drawing(points, n) {}

Line::Line(Point p1, Point p2){
    points.push_back(p1);
    points.push_back(p2);
}

void Line::draw(ShadowBuffer& sb) {
    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;
    int x2 = (int)points[1].x;
    int y2 = (int)points[1].y;

    float deltaX = (x2 - x1);
    float deltaY = (y2 - y1);
    float error = 0;
    float deltaErr = fabs(deltaY/deltaX);

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    int y = (int)y1;
    for (int x = (int)x1; x <= (int)x2; x++) {
        sb.plot(x,y, color);
        error = error + deltaErr;

        while (error >= 0.5 && y != y2) {
            sb.plot(x,y, color);
            int sign = (y2 > y1) ? 1: -1;
            y = y + sign;
            error = error - 1;
        }
    }
}

void Line::draw(ShadowBuffer& sb, Point const baseStart, int const radius, Color startColor, Color endColor) {
    //Create color which has rgb values of differences between startColor and endColor
    Color diffStartEnd(endColor.r, endColor.g, endColor.b);
    diffStartEnd.r -= startColor.r;
    diffStartEnd.g -= startColor.g;
    diffStartEnd.b -= startColor.b;

    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;
    int x2 = (int)points[1].x;
    int y2 = (int)points[1].y;

    float deltaX = (x2 - x1);
    float deltaY = (y2 - y1);
    float error = 0;
    float deltaErr = fabs(deltaY/deltaX);

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    Color c;
    float d;
    int y = (int)y1;
    for (int x = (int)x1; x <= (int)x2; x++) {
        d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));
        float percentage = ((d / radius));
        if (percentage > 1) percentage = 1;
        c.r = startColor.r + diffStartEnd.r * percentage;
        c.g = startColor.g + diffStartEnd.g * percentage;
        c.b = startColor.b + diffStartEnd.b * percentage;

        sb.plot(x, y, c);
        error = error + deltaErr;

        while (error >= 0.5 && y != y2) {

            int sign = (y2 > y1) ? 1: -1;
            y = y + sign;
            error = error - 1;

            sb.plot(x, y, c);
            d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));
            int percentage = ((d / radius));
            if (percentage > 1) percentage = 1;
            c.r = startColor.r + diffStartEnd.r * percentage;
            c.g = startColor.g + diffStartEnd.g * percentage;
            c.b = startColor.b + diffStartEnd.b * percentage;
        }
    }
}

void Line::draw(ShadowBuffer& sb, Point const baseStart, float * radius, Color * colors, int n) {
    if (radius[0] != 0) cout << "WARNING: First element of radius should be a ZERO" << endl;
    //Create color which has rgb values of differences between startColor and endColor
    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;
    int x2 = (int)points[1].x;
    int y2 = (int)points[1].y;

    float deltaX = (x2 - x1);
    float deltaY = (y2 - y1);
    float error = 0;
    float deltaErr = fabs(deltaY/deltaX);

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    Color c;
    float d;
    int y = (int)y1;
    for (int x = (int)x1; x <= (int)x2; x++) {
        d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));

        int segmentId = 1;
        while (d > radius[segmentId] && segmentId < n - 1) {
            ++segmentId;
        }

        double percentage;
        if (segmentId == n) {
            percentage = 1;
        } else {
            percentage = (d - radius[segmentId - 1]) / (radius[segmentId] - radius[segmentId - 1]);
        }
        if (percentage > 1) percentage = 1;

        c.r = colors[segmentId - 1].r + (colors[segmentId].r - colors[segmentId - 1].r) * percentage;
        c.g = colors[segmentId - 1].g + (colors[segmentId].g - colors[segmentId - 1].g) * percentage;
        c.b = colors[segmentId - 1].b + (colors[segmentId].b - colors[segmentId - 1].b) * percentage;

        sb.plot(x, y, c);
        error = error + deltaErr;

        while (error >= 0.5 && y != y2) {

            int sign = (y2 > y1) ? 1: -1;
            y = y + sign;
            error = error - 1;

            sb.plot(x, y, c);
            d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));
            int segmentId = 1;
            while (d > radius[segmentId] && segmentId < n - 1) {
                ++segmentId;
            }

            double percentage;
            if (segmentId == n) {
                percentage = 1;
            } else {
                percentage = (d - radius[segmentId - 1]) / (radius[segmentId] - radius[segmentId - 1]);
            }
            if (percentage > 1) percentage = 1;

            c.r = colors[segmentId - 1].r + (colors[segmentId].r - colors[segmentId - 1].r) * percentage;
            c.g = colors[segmentId - 1].g + (colors[segmentId].g - colors[segmentId - 1].g) * percentage;
            c.b = colors[segmentId - 1].b + (colors[segmentId].b - colors[segmentId - 1].b) * percentage;

        }
    }
}



void Line::drawChopped(ShadowBuffer& sb, Point const baseStart, int const radius, Color startColor, Color endColor, int n) {
    //Create color which has rgb values of differences between startColor and endColor
    Color diffStartEnd(endColor.r, endColor.g, endColor.b);
    diffStartEnd.r -= startColor.r;
    diffStartEnd.g -= startColor.g;
    diffStartEnd.b -= startColor.b;

    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;
    int x2 = (int)points[1].x;
    int y2 = (int)points[1].y;

    float deltaX = (x2 - x1);
    float deltaY = (y2 - y1);
    float error = 0;
    float deltaErr = fabs(deltaY/deltaX);

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    Color c;
    float d;
    float * segmentPercentage = new float[n];
    for (int i = 0; i < n; i++) {
        segmentPercentage[i] = (float)i / n;
    }

    int y = (int)y1;
    for (int x = (int)x1; x <= (int)x2; x++) {
        d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));
        float percentage = ((d / radius));

        int segmentId = 0;
        while (segmentPercentage[segmentId] < percentage && segmentId < n) {
            ++segmentId;
        }
        percentage = segmentPercentage[segmentId];

        if (percentage > 1) percentage = 1;
        c.r = startColor.r + diffStartEnd.r * percentage;
        c.g = startColor.g + diffStartEnd.g * percentage;
        c.b = startColor.b + diffStartEnd.b * percentage;

        sb.plot(x, y, c);
        error = error + deltaErr;

        while (error >= 0.5 && y != y2) {

            int sign = (y2 > y1) ? 1: -1;
            y = y + sign;
            error = error - 1;

            sb.plot(x, y, c);
            d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));
            int percentage = ((d / radius));

            int segmentId = 0;
            while (segmentPercentage[segmentId] < percentage && segmentId < n) {
                ++segmentId;
            }

            percentage = segmentPercentage[segmentId];
            if (percentage > 1) percentage = 1;

            c.r = startColor.r + diffStartEnd.r * percentage;
            c.g = startColor.g + diffStartEnd.g * percentage;
            c.b = startColor.b + diffStartEnd.b * percentage;
        }
    }
}

void Line::drawChopped(ShadowBuffer& sb, Point const baseStart, float * radius, Color * colors, int n, int nSegment) {
    if (radius[0] != 0) cout << "WARNING: First element of radius should be a ZERO" << endl;
    //Create color which has rgb values of differences between startColor and endColor
    int x1 = (int)points[0].x;
    int y1 = (int)points[0].y;
    int x2 = (int)points[1].x;
    int y2 = (int)points[1].y;

    float deltaX = (x2 - x1);
    float deltaY = (y2 - y1);
    float error = 0;
    float deltaErr = fabs(deltaY/deltaX);

    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    Color c;
    float d;
    float * segmentPercentage = new float[nSegment];
    for (int i = 0; i < nSegment; i++) {
        segmentPercentage[i] = (float)i / nSegment;
    }

    int y = (int)y1;
    for (int x = (int)x1; x <= (int)x2; x++) {
        d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));

        int segmentId = 1;
        while (d > radius[segmentId] && segmentId < n - 1) {
            ++segmentId;
        }

        double percentage;
        if (segmentId == n) {
            percentage = 1;
        } else {
            percentage = (d - radius[segmentId - 1]) / (radius[segmentId] - radius[segmentId - 1]);

            int choppedSegmentId = 0;
            while (segmentPercentage[choppedSegmentId] < percentage && choppedSegmentId < nSegment) {
                ++choppedSegmentId;
            }
            percentage = segmentPercentage[choppedSegmentId];
        }
        if (percentage > 1) percentage = 1;

        c.r = colors[segmentId - 1].r + (colors[segmentId].r - colors[segmentId - 1].r) * percentage;
        c.g = colors[segmentId - 1].g + (colors[segmentId].g - colors[segmentId - 1].g) * percentage;
        c.b = colors[segmentId - 1].b + (colors[segmentId].b - colors[segmentId - 1].b) * percentage;

        sb.plot(x, y, c);
        error = error + deltaErr;

        while (error >= 0.5 && y != y2) {

            int sign = (y2 > y1) ? 1: -1;
            y = y + sign;
            error = error - 1;

            sb.plot(x, y, c);
            d = sqrt(fabs(pow(baseStart.x - x, 2) + pow(baseStart.y - y, 2)));
            int segmentId = 1;
            while (d > radius[segmentId] && segmentId < n - 1) {
                ++segmentId;
            }

            double percentage;
            if (segmentId == n) {
                percentage = 1;
            } else {
                percentage = (d - radius[segmentId - 1]) / (radius[segmentId] - radius[segmentId - 1]);

                int choppedSegmentId = 0;
                while (segmentPercentage[choppedSegmentId] < percentage && choppedSegmentId < nSegment) {
                    ++choppedSegmentId;
                }
                percentage = segmentPercentage[choppedSegmentId];
            }
            if (percentage > 1) percentage = 1;

            c.r = colors[segmentId - 1].r + (colors[segmentId].r - colors[segmentId - 1].r) * percentage;
            c.g = colors[segmentId - 1].g + (colors[segmentId].g - colors[segmentId - 1].g) * percentage;
            c.b = colors[segmentId - 1].b + (colors[segmentId].b - colors[segmentId - 1].b) * percentage;

        }
    }
}

Point Line::getPoint1(){
    return points[0];
}

Point Line::getPoint2(){
    return points[1];
}

Point Line::projectPointToLine(Point const p) {
    Point p1 = points[0];
    Point p2 = points[1];
    //get the formula of current line
    
    //get the gradient
    float lineGradient = (p2.y - p1.y) / (p2.x - p1.x);

    //the formula will be y = m(x - getPoint1.x) + getPoint1.y

    //get the perpendicular gradient
    float perpendicularGradient = -1 / lineGradient;

    //get the c of the perpendicular line y = m(x) + c
    float c = p.y - (perpendicularGradient * p.x);

    //the formula of perpendicular line will be y = m(x) + c

    //now equalize both formula to find the projected point in line

    //kOfX is coefficient of x
    float kOfX = perpendicularGradient - lineGradient;
    float rem = (-lineGradient * p1.x) + p1.y + c;

    float x = rem / kOfX;
    float y = lineGradient * (x - p1.x) + p1.y;
    float z = 0;

    return Point(x, y, z);
}