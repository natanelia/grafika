#include "Shape.h"

Shape::Shape(vector<Point>& points) : Drawing(points) {}

Shape::Shape(Point points[], int n) : Drawing(points, n) {}
Shape::~Shape(){}

void Shape::draw(ShadowBuffer& sb) {
    scanLineFill(points,sb);
    drawBorder(borderColor, sb);
}

void Shape::drawClipped(ShadowBuffer& sb, Point min, Point max, float scale) {
    clip(min, max, scale);
    scanLineFill(clippedPoint,sb);
    drawBorder(borderColor, sb);
}

vector<Point> Shape::sortVector(vector<Point> v) {
    int i, j, numLength = v.size();
    Point key;
    for(j = 1; j < numLength; j++) {  // Start with 1 (not 0)
        key = v[j];
        for(i = j - 1; (i >= 0) && (v[i].x > key.x); i--) { // Smaller values move up
            v[i+1] = v[i];
        }
        v[i+1] = key;    //Put key into its proper location
    }
    return v;
}

int Shape::findIntersection(Point& p1, Point& p2, int y, int &x) {
    if (p1.y == p2.y) {
        return false;
    }

    x = (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y) + p1.x;
    
    int isInsideEdgeX;
    int isInsideEdgeY;

    if(p1.x < p2.x) 
        isInsideEdgeX = (p1.x <= x) && (x <= p2.x);
    else 
        isInsideEdgeX = (p2.x <= x) && (x <= p1.x);

    if(p1.y < p2.y)
        isInsideEdgeY = (p1.y <= y) && (y <= p2.y);
    else
        isInsideEdgeY = (p2.y <= y) && (y <= p1.y);

    return isInsideEdgeX && isInsideEdgeY;
}

void Shape::scanLineFill(vector<Point> v, ShadowBuffer& sb)
{       
    Point p1, p2;   
    int edgesSize = v.size();
    Point * tipPoints = getTipPoints();
    for(int i = tipPoints[0].y; i <= tipPoints[1].y; i++) {
        vector<Point> ListOfIntersectPoints;
        for(int j = 0; j < edgesSize; j++) {
            if (j != (edgesSize - 1)) {
                p1 = v[j];
                p2 = v[j+1];
            } else {
                p1 = v[j];
                p2 = v[0];
            }
            int intersectX;
            if (findIntersection(p1,p2,i,intersectX)) {
                if(p1.y > p2.y) {
                    std::swap(p1,p2);
                }

                // i = y
                if (i != p2.y) {
                    Point intersect(intersectX, i, 0);
                    ListOfIntersectPoints.push_back(intersect);
                }
                //ListOfIntersectPoints.push_back(intersect);
            }
        }
        vector<Point> result = sortVector(ListOfIntersectPoints);
        int intersectPointsSize = result.size();
        Color d(225, 0, 0);
        for(int j = 0; j < intersectPointsSize-1; j+=2) {
            vector<Point> p;
            p.push_back(result[j]);
            p.push_back(result[j+1]);
            Line line(p);
            line.color = this->color;
            line.draw(sb);
            //drawLine(result[j].x,result[j].y,result[j+1].x,result[j+1].y,d);
        }
    }
}

void Shape::drawBorder(ShadowBuffer& sb, Color c){
    for(int i = 0; i< points.size(); i++){
        vector<Point> p;
        if(i==points.size()-1){
            p.push_back(points[i]);
            p.push_back(points[0]);
    
        }else{
            p.push_back(points[i]);
            p.push_back(points[i+1]);
        }
        Line line(p);
        line.color = c;
        line.draw(sb);
    }
}

void Shape::setColor(Color color){
    this->color = color;
}

