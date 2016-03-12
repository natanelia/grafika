#include "Shape.h"
#include <stdexcept> 

Shape::Shape():Drawing(){}

Shape::Shape(vector<Point>& points) : Drawing(points) {
    //this->type = DEFAULT_FILL;
}

Shape::Shape(Point points[], int n) : Drawing(points, n) {}
Shape::~Shape(){}

void Shape::draw(ShadowBuffer& sb) {
    vector<Point> result;
    addBezier(&result);

    // for(int i=0; i<result.size()-1; i++) {
    //     Line line(result[i],result[i+1]);
    //     line.color = Color(0,0,225);
    //     line.draw(sb);
    // }
    
    scanLineFill(sb, result);
    //result.clear();
    //drawBorder(sb, this->color );
}

void Shape::drawClipped(ShadowBuffer& sb, Point min, Point max, float scale) {
    clip(min, max, scale);
    scanLineFill(sb, clippedPoints);
    //drawBorder(sb, borderColor);
}

vector<Point> Shape::sortVector(vector<Point> v) {
    int i, j, numLength = v.size();
    Point key;
    for(j = 1; j < numLength; j++) {   // Start with 1 (not 0)
        key = v[j];
        for(i = j - 1; (i >= 0) && (v[i].x > key.x); i--) {  // Smaller values move up
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
    float xFloat = (p2.x - p1.x) * ((float)y - p1.y) / (p2.y - p1.y) + p1.x;
    x = (int)xFloat;
     //cout<< "x, y =" << x << ", " << y<< endl;
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
int Shape::floatToInt(float a){
    float temp= a - floor(a);
    if(temp > 0.5){
        return (int) a +1;
    }else 
        return (int) a;
}

void Shape::scanLineFill(ShadowBuffer& sb, vector<Point> v) {
    Util util;
    Point basePoint(0,0,0);
    ColorTable ct("assets/ColorTable.ct");
    Image texture = util.convertImageFile("assets/texture-grass.txt", ct);
    Color ** textureCache = texture.getCached();
    Point textureWH = texture.getWidthAndHeight();
    int textureWidth = textureWH.x;
    int textureHeight = textureWH.y;

    Point p1, p2;   
    int edgesSize = v.size();
    Point * tipPoints = getTipPoints();
    vector<map<int,int> > brensenham;
    for(int i=1; i < v.size(); i++){
        Line l(v[i-1], v[i]);
        brensenham.push_back(l.getLinePoints());
    }
    Line l(v[v.size()-1], v[0]);
    brensenham.push_back(l.getLinePoints());

    for(int i = tipPoints[0].y; i <= tipPoints[1].y; i++) {
        vector<Point> ListOfIntersectPoints;
        // for(int j = 0; j < edgesSize; j++) {
        //     if (j != (edgesSize - 1)) {
        //         p1 = v[j];
        //         p2 = v[j+1];
        //     } else {
        //         p1 = v[j];
        //         p2 = v[0];
        //     }
        //     int intersectX;
        //     if((floatToInt(p1.y)==floatToInt(p2.y))&&(floatToInt(p1.x)==floatToInt(p2.x))&&(floatToInt(p1.y)==i)){
        //         Point intersect((int)p1.x, i, 0);
        //         ListOfIntersectPoints.push_back(intersect);
        //     }
        //     else if (findIntersection(p1,p2,i,intersectX)) {
        //         if(p1.y > p2.y) {
        //             std::swap(p1,p2);
        //         }

        //         //if (i != p2.y) {
        //             Point intersect(intersectX, i, 0);
        //             ListOfIntersectPoints.push_back(intersect);
        //         //}
        //     }
        // }
        for(int j=0; j < brensenham.size(); j++){
            try{
                if (brensenham[j][i]) {
                    ListOfIntersectPoints.push_back(Point(brensenham[j][i], i, 0));
                }
            }catch(const std::out_of_range& oor) {

            }
        }
        vector<Point> result = sortVector(ListOfIntersectPoints);
        int intersectPointsSize = result.size();
        Color d(225, 0, 0);
        for(int j = 0; j < intersectPointsSize-1; j+=2) {
            Line line(result[j], result[j + 1]);
            line.color = this->color;
            //line.draw(sb);
            //line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));
            line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);
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
    this->borderColor = color;
}

vector<Line>  Shape::initAvailable(vector<Point> v, ShadowBuffer& sb) {
    vector<Line>  available;
    
    for(int i=0; i < v.size()-1; i+=2) {
        vector<Line> init;    
        Line line(v[i],v[i+1]);
        available.push_back(line);
    }
    return available;
}

void Shape::drawAvailable(vector<Line> available, vector<Point> demand, ShadowBuffer& sb, Color c) {

    for (int j=0; j<demand.size()-1; j+=2) {
        vector<Line> newAvailable;
        for (int i= 0; i < available.size(); i++ ) {
            if (available[i].getPoint2().x<=available[i].getPoint1().x) { //sudah tidak ada slot
                   
            } else if ((available[i].getPoint1().x <= demand[j].x) && (demand[j+1].x <= available[i].getPoint2().x)) { //demand berada di tengah
                Line split1(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));

                Line split2(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                newAvailable.push_back(split1);
                newAvailable.push_back(split2);

                Line line(demand[j], demand[j+1]);
                line.color = c;
                line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));
            } else if (available[i].getPoint1().x <= demand[j].x) { //demand lebih banyak kebelakang
                Line split(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));
                newAvailable.push_back(split);

                Line line(demand[j], Point(available[i].getPoint2().x,demand[j].y,0));
                line.color = c;
                line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));

            } else if (demand[j+1].x <= available[i].getPoint2().x) { //demand lebih banyak di depan
                Line split(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                Line line(Point(available[i].getPoint1().x,demand[j+1].y,0),demand[j+1]);
                line.color = c;
                line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));

                newAvailable.push_back(split);
            } else {
                newAvailable.push_back(available[i]); 
            }
        }
        //available.clear();
        available = newAvailable;
        //update info available
        //Available.push_back(newAvailable);
    }
}

void Shape::scanLineIntersect(ShadowBuffer& sb, Shape available) {
    Point p1, p2;   

    int nAvailable = available.points.size();

    int nDemand = points.size();
    int a = 0;
    available.draw(sb);
    Point * tipPoints = available.getTipPoints();
    //cout<< "ymin : "<<tipPoints[0].y<< " ymax : "<<tipPoints[1].y<<endl;
    for (int i = tipPoints[0].y; i <= tipPoints[1].y; i++) {  

    //Line line(Point(1,i,0),Point(500,i,0));
      //  line.color= Color(225,0,0);
        //line.draw(sb);
        //for (int k = 0; k < nAvailable; k++) {
            vector<Point> ListOfIntersectPoints;
            //Shape tempShape = pointToPrint[k];
            int edgesSize = available.points.size();
            //Color c = Color(tempShape.points[edgesSize-1].x,tempShape.points[edgesSize-1].y + 180 - (int)(i / 2),tempShape.points[edgesSize-1].z); 

            for (int j = 0; j < edgesSize ; j++) {
                //cout<< "GARIS ke-"<<j<<endl;
                if (j != (edgesSize - 1)) {
                    p1 = available.points[j];
                    p2 = available.points[j+1];
                } else {
                    p1 = available.points[j];
                    p2 = available.points[0];
                }

                int intersectX;

                if (findIntersection(p1,p2,i,intersectX)){
                    //cout<< intersectX<<endl;
                    if (p1.y > p2.y) {
                        std::swap(p1,p2);
                    }
                    Point intersect(intersectX, i,0);

                    if (intersect.y != p2.y) 
                    ListOfIntersectPoints.push_back(intersect);
                }
            }
            vector<Point> sort = sortVector(ListOfIntersectPoints);
            //cout<<"setelah sort"<<endl;
            // for(int i=0; i<sort.size(); i++){
            //     //cout<< "x, y =" << sort[i].x << ", " << sort[i].y<< endl;
            // }
            if(sort.size()>0) {
                vector<Line> resultAvailable = initAvailable(sort,sb);
                vector<Point> ListOfIntersectPoints2;
                int edgesSize2 = points.size();
                for (int j = 0; j < (edgesSize2 ); j++) {
                    if (j != (edgesSize2 - 1)) {
                        p1 = points[j];
                        p2 = points[j+1];
                    } else {
                        p1 = points[j];
                        p2 = points[0];
                    }

                    int intersectX;

                    if (findIntersection(p1,p2,i,intersectX)){
                        if (p1.y > p2.y) {
                            std::swap(p1,p2);
                        }
                        Point intersect(intersectX, i,0);
                        if (intersect.y == p2.y) continue;
                        ListOfIntersectPoints2.push_back(intersect);
                    }
                }
                vector<Point> resultDemand = sortVector(ListOfIntersectPoints2);
                drawAvailable(resultAvailable, resultDemand,sb, this->color);
            }
        //} 
    }
}

int Shape::factorial(int n) 
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}

float Shape::Bernstein(int i, int n, float t) {
    int binomial = factorial(n)/(factorial(n-i)*factorial(i));
    float br = binomial*pow(t,i)*pow((1-t),(n-i));
    return br;
}

void Shape::Bezier (vector<Point> control, vector<Point> *result)
{
    float t;
    int n = control.size()-1;
    for (t = 0.0; t < 1.0; t += 0.1)
    {
        float xt =0;
        float yt =0;
        for(int i=0; i<=n; i++) {
            xt += control[i].x*Bernstein(i,n,t);
            yt += control[i].y*Bernstein(i,n,t);

        }
        if (result->size()) {
            if (result->at(result->size()-1).x == xt || result->at(result->size()-1).y == yt) {
                /* do nothing */
            } else {
                result->push_back(Point(xt,yt,0,0));
            }
        } else {
            result->push_back(Point(xt,yt,0,0));
        }
    }
}

void Shape::addBezier(vector<Point> *result) {
    vector<Point> temp;
    temp = points;
    for(int i=0; i<temp.size(); i++) {
       
        if(temp[i].tag==0) {

            vector<Point> control;
            vector<Point> bezier;
            control.push_back(temp[i]);
            i++;
            while(i<temp.size() && temp[i].tag==1) {

                control.push_back(temp[i]);
                i++;
            }
            if(i>=temp.size()) {
                control.push_back(temp[0]);
               
            }
            else {
                control.push_back(temp[i]);
                if(i>=temp.size())
                control.push_back(temp[0]);
            }
            //jika isi control>2, berarti bezier
           
            if(control.size()>2) {
                Bezier(control, &bezier);
                for(int j=0; j<bezier.size(); j++){
                    result->push_back(bezier[j]);
                }
                
               
            }
            else {
                for(int j=0; j<control.size(); j++){
                    result->push_back(control[j]);
                }
            }
            i--;
        }
    }
}