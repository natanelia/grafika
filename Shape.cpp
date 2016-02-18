#include "Shape.h"

Shape::Shape(vector<Point>& points) : Drawing(points) {}

Shape::Shape(Point points[], int n) : Drawing(points, n) {}

void Shape::draw(ShadowBuffer& sb) {
    vector<Triangle> triangles = Triangulate::VectorToTriangleVector(points);
    for (int i = 0; i < triangles.size(); i++){
        fillTriangle(triangles[i].P1, triangles[i].P2,triangles[i].P3, this->color, sb);
    }
}

vector<Point> Shape::listAllPointinLine (Point P1, Point P2) {
    //this->drawToBuffer();
    long int location;
    int x1, x2, y1, y2, x, b,a;
    vector<Point> v;

    x1 = P1.x;
    y1 = P1.y;
    x2 = P2.x;
    y2 = P2.y;

    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if(steep)
  {
    std::swap(x1, y1);
    std::swap(x2, y2);
  }

  if(x1 > x2)
  {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }

  //std::swap(x1,x2);

  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);

  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;

  const int maxX = (int)x2;

  for(int x=(int)x1; x<=maxX; x++)
  {

    if(steep)
    {
        a=y;
        b=x;
    }
    else
    {
        a=x;
        b=y;
    }
    Point P;
    P.x = a;
    P.y = b;
    v.push_back(P);

    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }

  }
  return v;
}

void Shape::fillTriangle(Point P1, Point P2, Point P3, Color c, ShadowBuffer& sb) {
    vector<Point> v1;
    vector<Point> v2;
    vector<Point> v3;

    //membuat list point dari besenhem 3 titik
    //P1 dan P2
    v1 = listAllPointinLine(P1,P2);
    v2 = listAllPointinLine(P1,P3);
    v3 = listAllPointinLine(P2,P3);

    vector<Point> vmax;
    Point psumber;

    for (int i=0 ; i<v1.size() ; i++){
        vector<Point> points;
        points.push_back(Point(P3.x, P3.y));
        points.push_back(Point(v1[i].x, v1[i].y));
        Line line(points);
        line.color = c;
        line.draw(sb);
    }
    for (int i=0 ; i<v2.size() ; i++){
        vector<Point> points;
        points.push_back(Point(P2.x, P2.y));
        points.push_back(Point(v2[i].x, v2[i].y));
        Line line(points);
        line.color = c;
        line.draw(sb);
    }

    for (int i=0 ; i<v3.size() ; i++){
        vector<Point> points;
        points.push_back(Point(P1.x, P1.y));
        points.push_back(Point(v3[i].x, v3[i].y));
        Line line(points);
        line.color = c;
        line.draw(sb);
    }
}