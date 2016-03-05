#include "Face.h"

Face::Face(){}

Face::Face(map<string, vector<Point> > point, int a, int b, int c, float s){
    Color color;
    vector<Point > points;
    scale = s;

    //head
    points = point.find("head")->second;
    Shape head(points);
    color = Color((int)points[points.size() - 1].x,(int)points[points.size() - 1].y,(int)points[points.size() - 1].z);
    head.setColor(color);
    head.points.erase(head.points.begin() + head.points.size() - 1);
    for (int i = 0; i < head.points.size(); i++){
        head.points.at(i).x *= scale;
        head.points.at(i).x += a;
        head.points.at(i).y *= scale;
        head.points.at(i).y += b;
        head.points.at(i).z *= scale;
        head.points.at(i).z += c;
    }
    face.push_back(head);
    normal_state.push_back(head);

    //eyes
    vector<vector<Point > > eyes_components;
    points = point.find("right_eyebrow")->second;
    eyes_components.push_back(points);
    points = point.find("left_eyebrow")->second;
    eyes_components.push_back(points);
    points = point.find("right_eye")->second;
    eyes_components.push_back(points);
    points = point.find("left_eye")->second;
    eyes_components.push_back(points);
    points = point.find("right_eyeball")->second;
    eyes_components.push_back(points);
    points = point.find("left_eyeball")->second;
    eyes_components.push_back(points);
    Eyes e(eyes_components,a,b,c,scale);
    eyes = e;

    //nose
    points = point.find("nose")->second;
    Shape nose(points);
    color = Color((int)points[points.size() - 1].x,(int)points[points.size() - 1].y,(int)points[points.size() - 1].z);
    nose.setColor(color);
    nose.points.erase(nose.points.begin() + nose.points.size() - 1);
    for (int i = 0; i < nose.points.size(); i++){
        nose.points.at(i).x *= scale;
        nose.points.at(i).x += a;
        nose.points.at(i).y *= scale;
        nose.points.at(i).y += b;
        nose.points.at(i).z *= scale;
        nose.points.at(i).z += c;
    }
    face.push_back(nose);
    normal_state.push_back(nose);

    //upper lip
    points = point.find("upper_lip")->second;
    Shape upperlip(points);
    color = Color((int)points[points.size() - 1].x,(int)points[points.size() - 1].y,(int)points[points.size() - 1].z);
    upperlip.setColor(color);
    upperlip.points.erase(upperlip.points.begin() + upperlip.points.size() - 1);
    for (int i = 0; i < upperlip.points.size(); i++){
        upperlip.points.at(i).x *= scale;
        upperlip.points.at(i).x += a;
        upperlip.points.at(i).y *= scale;
        upperlip.points.at(i).y += b;
        upperlip.points.at(i).z *= scale;
        upperlip.points.at(i).z += c;
    }
    face.push_back(upperlip);
    normal_state.push_back(upperlip);

    //lower head
    vector<vector<Point > > lowerhead_components;
    points = point.find("lower_lip")->second;
    lowerhead_components.push_back(points);
    points = point.find("jaw")->second;
    lowerhead_components.push_back(points);
    LowerHead lh(lowerhead_components,a,b,c,scale);
    lowerHead = lh;
}

Face& Face::operator= (const Face& f){
    this->face = f.face;
    this->eyes = f.eyes;
    this->lowerHead = f.lowerHead;
    this->scale = f.scale;
    return *this;
}

void Face::draw(ShadowBuffer& sb){
    face.at(0).draw(sb);
    face.at(1).drawBorder(sb,face.at(1).borderColor);
    lowerHead.draw(sb);
    face.at(2).draw(sb);
    eyes.draw(sb);
}

void Face::smile(){
    face.clear();
    face.push_back(normal_state.at(0));
    face.push_back(normal_state.at(1));
    face.push_back(normal_state.at(2));
    float top = 10000;
    float min = 10000;
    float max = 0;
    for (int i = 0; i < face.at(2).points.size(); i++){
        if (min > face.at(2).points.at(i).x)
            min = face.at(2).points.at(i).x;
        if (max < face.at(2).points.at(i).x)
            max = face.at(2).points.at(i).x;
        if (top > face.at(2).points.at(i).y)
            top = face.at(2).points.at(i).y;
    }
    float median = (min + max) / 2;
    int median_index;
    for(int i = 0; i < face.at(2).points.size(); i++){
        face.at(2).points.at(i).x -= median;
        face.at(2).points.at(i).x *= 1.2;
        face.at(2).points.at(i).x += median;
        face.at(2).points.at(i).y -= top;
        face.at(2).points.at(i).y *= 0.5;
        face.at(2).points.at(i).y += top;
    }
    for(int i = 0; i < face.at(0).points.size(); i++){
        if (face.at(0).points.at(i).x == median)
            median_index = i;
    }

    for (int i = median_index - 2; i <= median_index + 2; i++){
        face.at(0).points.at(i).x -= median;
        face.at(0).points.at(i).x *= 1.2;
        face.at(0).points.at(i).x += median;
        face.at(0).points.at(i).y -= top;
        face.at(0).points.at(i).y *= 0.5;
        face.at(0).points.at(i).y += top;
    }
    lowerHead.smile(top);
}

void Face::openMouth(){
    face.clear();
    face.push_back(normal_state.at(0));
    face.push_back(normal_state.at(1));
    face.push_back(normal_state.at(2));
    float top = 10000;
    float min = 10000;
    float max = 0;
    for (int i = 0; i < face.at(2).points.size(); i++){
        if (min > face.at(2).points.at(i).x)
            min = face.at(2).points.at(i).x;
        if (max < face.at(2).points.at(i).x)
            max = face.at(2).points.at(i).x;
        if (top > face.at(2).points.at(i).y)
            top = face.at(2).points.at(i).y;
    }
    float median = (min + max) / 2;
    int median_index;
    for(int i = 0; i < face.at(2).points.size(); i++){
        face.at(2).points.at(i).x -= median;
        face.at(2).points.at(i).x *= 1.4;
        face.at(2).points.at(i).x += median;
        face.at(2).points.at(i).y -= top;
        face.at(2).points.at(i).y *= 0.5;
        face.at(2).points.at(i).y += top;
    }
    for(int i = 0; i < face.at(0).points.size(); i++){
        if (face.at(0).points.at(i).x == median)
            median_index = i;
    }

    for (int i = median_index - 2; i <= median_index + 2; i++){
        face.at(0).points.at(i).x -= median;
        face.at(0).points.at(i).x *= 1;
        face.at(0).points.at(i).x += median;
        face.at(0).points.at(i).y -= top;
        face.at(0).points.at(i).y *= 1;
        face.at(0).points.at(i).y += top;
    }
    lowerHead.smile(top);
}