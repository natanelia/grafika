#include "Image.h"

Image::Image() : Drawing() {}

Image::Image(vector<Point>& points, vector<Color>& colors) : Drawing(points) {
    for (int i = 0; i < colors.size(); ++i) {
        this->colors.push_back(colors[i]);
    }
}

Image::Image(Point points[], Color colors[], int n) : Drawing(points, n) {
    for (int i = 0; i < n; ++i) {
        this->colors.push_back(colors[i]);
    }
}

Image::Image(vector<Point>& points, vector<Color>& colors, Point position){
    for (int i = 0; i < colors.size(); ++i) {
        this->colors.push_back(colors[i]);
    }
    this->position = position;
    translate(position.x, position.y,0);
}

void Image::draw(ShadowBuffer& sb) {
    //struct fb_var_screeninfo vinfo;
    for (int i = 0; i < points.size(); ++i) {
        if (points[i].x>=0 && points[i].x<=1366 && points[i].y<=768 && points[i].y>=0)
        sb.plot((int)(points[i].x), (int)(points[i].y), colors[i]);
    }
}

void Image::drawName(ShadowBuffer& sb) {
    //struct fb_var_screeninfo vinfo;
    for (int i = 0; i < points.size(); ++i) {
        if (points[i].x>=380 && points[i].x<=1366 && points[i].y<=768 && points[i].y>=100)
        sb.plot((int)(points[i].x), (int)(points[i].y), colors[i]);
    }
}

void Image::draw(ShadowBuffer& sb, int scaleX, int scaleY) {
    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < scaleY; ++j) {
            for (int k = 0; k < scaleX; ++k) {
                sb.plot((int)(points[i].x * scaleX) + k, (int)(points[i].y * scaleY) + j, colors[i]);
            }
        }
    }
}

Color ** Image::getCached() {
    Point * tipPoints = getTipPoints();
    int width = tipPoints[1].x - tipPoints[0].x + 1;
    int height = tipPoints[1].y - tipPoints[0].y + 1;


    Color ** pixels = new Color * [height];
    for (int i = 0; i < height; ++i) {
        pixels[i] = new Color[width];
        for (int j = 0; j < width; ++j) {
            pixels[i][j] = Color();
        }
    }


    for (int i = 0; i < points.size(); ++i) {
        pixels[(int)(points[i].y) - (int)(tipPoints[0].y)][(int)(points[i].x) - (int)(tipPoints[0].x)] = colors[i];
    }

    delete [] tipPoints;
    
    return pixels;
}

Point& Image::getWidthAndHeight() {
    Point * tipPoints = getTipPoints();
    int width = tipPoints[1].x - tipPoints[0].x;
    int height = tipPoints[1].y - tipPoints[0].y;

    Point * ret = new Point(width, height, 0);
    return *ret;
}

void Image::setPosition(Point p) {
    translate(p.x - position.x, p.y - position.y,0);
    this->position = p;    
}


void Image::project2dPos(){
    Point * tipPoints = getTipPoints();
    float factor;
    if(position.x > (tipPoints[1].x-tipPoints[0].x)/2)
        factor = 1.003;
    else
        factor = 1.001;

    float newX = (position.x * pow((factor),position.z * 0.1));
    float newY = (position.y * pow((factor),position.z * 0.1));
    Point p(newX,newY,0);
    setPosition(p);
}