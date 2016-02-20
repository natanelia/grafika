#include "Image.h"

Image::Image(vector<Point>& points) : Drawing(points) {}

Image::Image(Point points[], int n) : Drawing(points, n) {}

void Image::draw(ShadowBuffer& sb) {
    for (int i = 0; i < points.size(); ++i) {
        sb.plot((int)(points[i].x), (int)(points[i].y), color);
    }
}