#include "ShapeGroup.h"

ShapeGroup::ShapeGroup(string objName, float offsetX, float offsetY, int scale) {
    Util util;
    map<string, vector<Point> > point = util.readObject("assets/coba3d.txt");
    vector<vector<Point> > points = util.convertPoint(point, objName, offsetX, offsetY, 0, scale,  scale, scale);
    for (int j = 0; j < points.size(); j++) {
        Shape shape(points[j]);
        vector<Point> * p = &points[j];
        Color c(p->at(p->size()-1).x,p->at(p->size()-1).y,p->at(p->size()-1).z);
        shape.setColor(c);
        // cout << "sebelum" << shape.points.size() << endl;
        shape.points.pop_back();
        // cout << "setelah" << shape.points.size() << endl;
        shapes.push_back(shape);
    }

}

void ShapeGroup::draw(ShadowBuffer& sb, float offsetX, float offsetY) {
    projectTo2D(offsetX,offsetY);
    /*for(int i=0; i<shapes.size(); i++) {
        Shape s(pointToPrint[i]);
        s.drawBorder(sb, Color(255,255,255));
    }*/
    scanLineFill3D(sb);

    /*for (int j = 0; j < pointToPrint.size(); j++) {
        Color c = Color(j*j*4,j*20,250-j*15);
        for(int i=0; i< pointToPrint[j].size(); i++){
            vector<Point> p;
            if(i==pointToPrint[j].size()-1){
                p.push_back(pointToPrint[j][i]);
                p.push_back(pointToPrint[j][0]);
        
            }else{
                p.push_back(pointToPrint[j][i]);
                p.push_back(pointToPrint[j][i+1]);
            }
            Line line(p);
            line.color = c;
            line.draw(sb);
        }
    }*/
}

void ShapeGroup::drawClipped(ShadowBuffer& sb, Point min, Point max, float scale) {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].drawClipped(sb, min, max, scale);
    }
}

void ShapeGroup::translate(float dX, float dY, float dZ) {
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].translation(dX, dY, dZ);

             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
}

void ShapeGroup::scale(float scaleX, float scaleY, float scaleZ, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].scale(scaleX, scaleY, scaleZ);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::rotateX(float degree, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].rotateX(degree);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::rotateY(float degree, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].rotateY(degree);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

void ShapeGroup::rotateZ(float degree, float offsetX, float offsetY, float offsetZ) {
    translate(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
    for (int i = 0; i < shapes.size(); i++) {
        for (int j=0; j<shapes[i].points.size();j++){
             shapes[i].points[j].rotateZ(degree);

                 //pembulatan
             shapes[i].points[j].setX(roundf(shapes[i].points[j].x * 100) / 100);
             shapes[i].points[j].setY(roundf(shapes[i].points[j].y * 100) / 100);
             shapes[i].points[j].setZ(roundf(shapes[i].points[j].z * 100) / 100);
        }
    }
    translate(offsetX,offsetY, offsetZ);
}

Point * ShapeGroup::getTipPoints() {

    Shape temp(pointToPrint[0]);
    Point * tipPoints = temp.getTipPoints();

    for (int i = 1; i < pointToPrint.size(); i++) {
        Point * tp = Shape(pointToPrint[i]).getTipPoints();
        if (tipPoints[0].x > tp[0].x) {
            tipPoints[0].x = tp[0].x;
        }

        if (tipPoints[0].y > tp[0].y) {
            tipPoints[0].y = tp[0].y;
        }

        if (tipPoints[1].x < tp[1].x) {
            tipPoints[1].x = tp[1].x;
        }

        if (tipPoints[1].y < tp[1].y) {
            tipPoints[1].y = tp[1].y;
        }
    }

    return tipPoints;
}

int ShapeGroup::findZMax(vector<Point> plan){
    int max = -99;
    for(int x = 0; x < plan.size(); x++){
        if (max < plan[x].z) {
            max = plan[x].z;
        }
    }
    return max;
}

void ShapeGroup::sortLayer(){
    int i, j, numLength = pointToPrint.size();
    vector<Point> key;
    for(j = 1; j < numLength; j++) { // Start with 1 (not 0)
        key = pointToPrint[j];
        for(i = j - 1; (i >= 0) && (findZMax(pointToPrint[i]) >= findZMax(key)); i--) { // Smaller values move up
            pointToPrint[i+1] = pointToPrint[i];
        }
        pointToPrint[i+1] = key;    //Put key into its proper location
    }
}

void ShapeGroup::projectTo2D(float offsetX, float offsetY){
    pointToPrint.clear();
    int a = 0;
    for(int i = shapes.size() - 1; i >= 0; --i){
        vector<Point> temp;
        for(int j = 0; j < shapes[i].points.size(); j++){
            float newX = (offsetX + (shapes[i].points[j].x - offsetX) * pow((1.01),shapes[i].points[j].z * 0.1));
            float newY = (offsetY + (shapes[i].points[j].y - offsetY) * pow((1.01),shapes[i].points[j].z * 0.1));
            Point p(newX, newY, shapes[i].points[j].z);
            temp.push_back(p);
        }
        // temp.push_back(Point(60, 170-a, 60));
        // a += 10;
        pointToPrint.push_back(temp);
    }
    sortLayer();
}

vector<Point> ShapeGroup::sortVector(vector<Point> v) {
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
int ShapeGroup::findIntersection(Point& p1, Point& p2, int y, int &x, int &z) {

    /*if (p1.y == p2.y && p1.y != y) {
        return false;
    }*/

    int yBottom;
    int yTop;
    int x1 = (int)p1.x;
    int y1 = (int)p1.y;
    int x2 = (int)p2.x;
    int y2 = (int)p2.y;
    
    if (y1 > y2) {
        yBottom = y1;
        yTop = y2;
    } else {
        yBottom = y2;
        yTop = y1;
    }

    if (y < yTop || y > yBottom) return false;

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

    int yl = (int)y1;
    for (int xl = (int)x1; xl <= (int)x2; xl++) {
        // sb.plot(x,y, color);
        if (yl == y && yl != yBottom) {
            x = xl;
            return true;
        }
        error = error + deltaErr;


        while (error >= 0.5 && (yl != y2)) {
            // sb.plot(x,y, color);
            if (yl == y && yl != yBottom) {
                x = xl;
                return true;
            }
            int sign = (y2 > y1) ? 1: -1;
            yl = yl + sign;
            error = error - 1;
        }
    }
    return false;
}
// bool ShapeGroup::findIntersection(Point p1, Point p2, int y, int &x, int &z) {
//     if (p1.y == p2.y) return false;

//     bool isInsideEdgeX;
//     bool isInsideEdgeY;

//     x = ((p2.x-p1.x) * (y-p1.y)) / (p2.y-p1.y) + p1.x;
//     z = 0;
    
//     if(p1.x < p2.x) { 
//         isInsideEdgeX = (p1.x <= x) && (x <= p2.x);
//     } else { 
//         isInsideEdgeX = (p2.x <= x) && (x <= p1.x);
//     }

//     if(p1.y < p2.y) {
//         isInsideEdgeY = (p1.y <= y) && (y <= p2.y);
//     } else {
//         isInsideEdgeY = (p2.y <= y) && (y <= p1.y);
//     }

//     return isInsideEdgeX && isInsideEdgeY;
// }

vector<Line>  ShapeGroup::initAvailable(vector<Point> v) {
    vector<Line>  available;
    
    for(int i=0; i < v.size()-1; i+=2) {
        vector<Line> init;    
        Line line(v[i],v[i+1]);
        available.push_back(line);
    }
    return available;
}


void ShapeGroup::splitAvailable(vector<Line>  &available, vector<Point> demand, ShadowBuffer& sb, Point basePoint, int textureWidth, int textureHeight, Color ** textureCache ){
    //vector<Line> available= Available[Available.size() - 1];
// cout<< "ADA RESULT "<<demand.size()<<endl;
    for (int j=0; j<demand.size()-1;j+=2) {
        vector<Line> newAvailable;
        for (int i= 0; i < available.size(); i++ ) {
            // if (available[i].getPoint2().x<=available[i].getPoint1().x) { //sudah tidak ada slot
            //     //newAvailable.push_back(available[i]);   
            // } else if (demand[j].x > available[i].getPoint2().x) { //demand berada di kanan available
            //     newAvailable.push_back(available[i]); 
            // } else if (demand[j+1].x < available[i].getPoint1().x) { //demand di kiri available
            //     newAvailable.push_back(available[i]); 
            // } else if ((available[i].getPoint1().x <= demand[j].x)&&(demand[j+1].x <= available[i].getPoint2().x)){ //demand berada di tengah
            //     Line split1(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));

            //     Line split2(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

            //     newAvailable.push_back(split1);
            //     newAvailable.push_back(split2);
            //     cout<< "ADA"<<endl;
            //     if (j+1 < demand.size()) {
            //         Line line(demand[j], demand[j+1]);
            //         //line.color = c;
            //         //line.draw(sb);
            //         line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);
            //     }
            // } else if (available[i].getPoint1().x <= demand[j].x) { //demand lebih banyak kebelakang
            //     Line split(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));
            //     newAvailable.push_back(split);
            //     cout<< "ADA"<<endl;;
            //     Line line(demand[j], Point(available[i].getPoint2().x,demand[j].y,0));
            //     //line.color = c;
            //     //line.draw(sb);
            //     line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);

            // } else if (demand[j+1].x <= available[i].getPoint2().x) { //demand lebih banyak di depan
            //     Line split(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());
            //     cout<< "ADA"<<endl;
            //     Line line(Point(available[i].getPoint1().x,demand[j+1].y,0),demand[j+1]);
            //     // line.color = c;
            //     // line.draw(sb);
            //     line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);
            //     newAvailable.push_back(split);
            // }
            if (available[i].getPoint2().x<=available[i].getPoint1().x) { //sudah tidak ada slot
                   
            } else if ((available[i].getPoint1().x <= demand[j].x) && (demand[j+1].x <= available[i].getPoint2().x)) { //demand berada di tengah
                Line split1(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));

                Line split2(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                newAvailable.push_back(split1);
                newAvailable.push_back(split2);

                Line line(demand[j], demand[j+1]);
                //line.color = c;
                line.draw(sb);
                // line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);
                //line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));
            } else if (available[i].getPoint1().x <= demand[j].x) { //demand lebih banyak kebelakang
                Line split(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));
                newAvailable.push_back(split);

                Line line(demand[j], Point(available[i].getPoint2().x,demand[j].y,0));
                // line.color = c;
                // line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));
                line.draw(sb);
                // line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);

            } else if (demand[j+1].x <= available[i].getPoint2().x) { //demand lebih banyak di depan
                Line split(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                Line line(Point(available[i].getPoint1().x,demand[j+1].y,0),demand[j+1]);
                // line.color = c;
                line.draw(sb);
                // line.draw(sb, line.getPoint1(), line.getPoint1().getDistance(line.getPoint2()), line.color, Color(line.color.r - 50, line.color.g - 50, line.color.b - 50));
                // line.drawTextured(sb, basePoint, textureWidth, textureHeight, textureCache);

                newAvailable.push_back(split);
            } else {
                newAvailable.push_back(available[i]); 
            }
        }
        
        //update info available
        //Available.push_back(newAvailable);
        available = newAvailable;
    }
}

void ShapeGroup::splitAvailable(vector<Line> &available, vector<Point> demand, Color c, ShadowBuffer& sb) {
    for (int j=0; j<demand.size()-1;j+=2) {
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
                line.draw(sb);
            } else if (available[i].getPoint1().x <= demand[j].x) { //demand lebih banyak kebelakang
                Line split(available[i].getPoint1(), Point(demand[j].x-1, available[i].getPoint1().y,0));
                newAvailable.push_back(split);

                Line line(demand[j], Point(available[i].getPoint2().x,demand[j].y,0));
                line.color = c;
                line.draw(sb);

            } else if (demand[j+1].x <= available[i].getPoint2().x) { //demand lebih banyak di depan
                Line split(Point(demand[j+1].x+1,available[i].getPoint2().y,0), available[i].getPoint2());

                Line line(Point(available[i].getPoint1().x,demand[j+1].y,0),demand[j+1]);
                line.color = c;
                line.draw(sb);

                newAvailable.push_back(split);
            } else {
                newAvailable.push_back(available[i]); 
            }
        }
        available = newAvailable;
    }
}


vector<vector<Line> > ShapeGroup::initAvailable(int x1, int x2) {
    vector<vector<Line> > available;
    vector<Line> init;
    Line l(Point(x1,0,0),Point(x2,0,0));
    init.push_back(l);
    available.push_back(init);

    return available;
}

void ShapeGroup::scanLineFill3D(ShadowBuffer& sb) {
    Point p1, p2;   
    Util util;
    /*Point basePoint(0,0,0);
    ColorTable ct("assets/ColorTable.ct");
    Image texture = util.convertImageFile("assets/texture-grass.txt", ct);
    Color ** textureCache = texture.getCached();
    Point textureWH = texture.getWidthAndHeight();
    int textureWidth = textureWH.x;
    int textureHeight = textureWH.y;*/


    int nShape = pointToPrint.size();
    int a = 0;
    // for(int i=0; i<1; i++){
    //     //Shape s = points[i];
    //     shapes[i].draw(sb);
    //     shapes[i].drawBorder(sb, Color(225,0,0));
    // }
    Shape as = shapes[0];
    /*for(int q=0; q<pointToPrint[0].size(); q++){
        cout<< "x= "<<as.points[q].x<<" y= "<<as.points[q].y<<" z= "<<as.points[q].z<<endl;

        cout<< "x= "<<pointToPrint[0][q].x<<" y= "<<pointToPrint[0][q].y<<endl;
    }*/
    Point * tipPoints = getTipPoints();
    for (int i = 0; i <= 600; i++) {
        //cout<<"sadfsd"<<tipPoints[0].y << "YG KE 2 "<< tipPoints[1].y<<endl;
        Line l(Point(0,0,0), Point(1000,0,0));
        vector<Line> available; //initAvailable(tipPoints[0].x,tipPoints[1].x);
        available.push_back(l);
        for (int k = 0; (k < nShape); k++) {
            vector<Point> ListOfIntersectPoints;
            Shape tempShape = pointToPrint[k];
            //tempShape.drawBorder(sb, Color(255,225,0));
            //tempShape.drawBorder(sb, Color(225,0,0));
            int edgesSize = tempShape.points.size();
            //Color c = shapes[k].color;

            for (int j = 0; j < edgesSize; j++) {
                if (j != (edgesSize - 1)) {
                    p1 = tempShape.points[j];
                    p2 = tempShape.points[j+1];
                } else {
                    p1 = tempShape.points[j];
                    p2 = tempShape.points[0];
                }

                int intersectX, intersectZ;

                if (findIntersection(p1,p2,i,intersectX, intersectZ)){
                    if (p1.y > p2.y) {
                        std::swap(p1,p2);
                    }

                    Point intersect(intersectX, i,intersectZ);
                    if (intersect.y != p2.y)
                    ListOfIntersectPoints.push_back(intersect);
                }
            }

            vector<Point> result = sortVector(ListOfIntersectPoints);
            if (result.size() > 0) {
                
                splitAvailable(available, result, shapes[k].color, sb);            
            }
        } 
    }
}

void ShapeGroup::build3D(int height, Point& lightSource, int const lightRadius) {
    int i,j;

    int batas = shapes.size();
    for (int k = 0; k < batas; k++) {
        for(int i = 0; i < shapes[k].points.size(); i++){
            if (i  != shapes[k].points.size() - 1) {
                j = i + 1;
            } else {
                j = 0;
            }

            vector<Point > p;
            p.push_back(shapes[k].points[i]);
            p.push_back(shapes[k].points[j]);
            Point temp(shapes[k].points[j].x,shapes[k].points[j].y,height,shapes[k].points[j].tag);
            p.push_back(temp);
            Point temp2(shapes[k].points[i].x,shapes[k].points[i].y,height,shapes[k].points[i].tag);
            p.push_back(temp2);
            Shape s(p);

            Color c;
            float percentage = ((float)lightSource.getDistance(shapes[k].points[i]) / (float)lightRadius);
            if (percentage > 1) percentage = 1;
            percentage *= percentage;
            c.r = (int) (float)shapes[k].color.r * percentage;
            c.g = (int) (float)shapes[k].color.g * percentage;
            c.b = (int) (float)shapes[k].color.b * percentage;
            c.print();
            s.setColor(c);

            shapes.push_back(s);
        }
        vector<Point > p;
        for(int i = 0; i < shapes[k].points.size();i++){
            Point temp(shapes[k].points[i].x,shapes[k].points[i].y,height,shapes[k].points[i].tag);
            p.push_back(temp);
        }
        Shape s(p);
        Color c;
        float percentage = ((float)lightSource.getDistance(s.points[0]) / (float)lightRadius);
        if (percentage > 1) percentage = 1;
        percentage *= percentage;
        c.r = (int) (float)shapes[k].color.r * percentage;
        c.g = (int) (float)shapes[k].color.g * percentage;
        c.b = (int) (float)shapes[k].color.b * percentage;
        c.print();
        s.setColor(Color());
        shapes.push_back(s);
    }
}


Point * ShapeGroup::getGroundTipPoints() {
    Point * tipPoints = shapes[0].getTipPoints();

    for (int i = 1; i < shapes.size(); i++) {
        Point * tp = shapes[i].getTipPoints();
        if (tipPoints[0].x > tp[0].x) {
            tipPoints[0].x = tp[0].x;
        }

        if (tipPoints[0].y > tp[0].y) {
            tipPoints[0].y = tp[0].y;
        }

        if (tipPoints[1].x < tp[1].x) {
            tipPoints[1].x = tp[1].x;
        }

        if (tipPoints[1].y < tp[1].y) {
            tipPoints[1].y = tp[1].y;
        }

        if (tipPoints[0].z > tp[0].z) {
            tipPoints[0].z = tipPoints[1].z = tp[0].z;
        }
    }

    return tipPoints;
}