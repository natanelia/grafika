#include "LowerHead.h"

LowerHead::LowerHead(){}

LowerHead::LowerHead(vector<vector<Point > > points, int a, int b, int c, float s){
    Color color;
    scale = s;

    //lower lip
    Shape lowerlip(points.at(0));
    color = Color((int)points[0][points[0].size() - 1].x,(int)points[0][points[0].size() - 1].y,(int)points[0][points[0].size() - 1].z);
    lowerlip.setColor(color);
    lowerlip.points.erase(lowerlip.points.begin() + lowerlip.points.size() - 1);
    for (int i = 0; i < lowerlip.points.size(); i++){
        lowerlip.points.at(i).x *= scale;
        lowerlip.points.at(i).x += a;
        lowerlip.points.at(i).y *= scale;
        lowerlip.points.at(i).y += b;
        lowerlip.points.at(i).z *= scale;
        lowerlip.points.at(i).z += c;
    }
    lowerhead.push_back(lowerlip);
    normal_state.push_back(lowerlip);

    //jaw
    Shape jaw(points.at(1));
    color = Color((int)points[1][points[1].size() - 1].x,(int)points[1][points[1].size() - 1].y,(int)points[1][points[1].size() - 1].z);
    jaw.setColor(color);
    jaw.points.erase(jaw.points.begin() + jaw.points.size() - 1);
    for (int i = 0; i < jaw.points.size(); i++){
        jaw.points.at(i).x *= scale;
        jaw.points.at(i).x += a;
        jaw.points.at(i).y *= scale;
        jaw.points.at(i).y += b;
        jaw.points.at(i).z *= scale;
        jaw.points.at(i).z += c;
    }
    lowerhead.push_back(jaw);
    normal_state.push_back(jaw);
}

LowerHead& LowerHead::operator= (const LowerHead& lh){
    this->lowerhead = lh.lowerhead;
    this-> scale = lh.scale;
    this->normal_state = lh.normal_state;
    return *this;
}

void LowerHead::draw(ShadowBuffer& sb){
    lowerhead.at(0).draw(sb);
    lowerhead.at(1).draw(sb);
}
void LowerHead::smile(float top){
    lowerhead.clear();
    lowerhead.push_back(normal_state.at(0));
    lowerhead.push_back(normal_state.at(1));
    float min = 10000;
    float max = 0;
    for (int i = 0; i < lowerhead.at(0).points.size(); i++){
        if (min > lowerhead.at(0).points.at(i).x)
            min = lowerhead.at(0).points.at(i).x;
        if (max < lowerhead.at(0).points.at(i).x)
            max = lowerhead.at(0).points.at(i).x;
    }
    float median = (min + max) / 2;

    for(int i = 0; i < lowerhead.at(0).points.size(); i++){
        lowerhead.at(0).points.at(i).x -= median;
        lowerhead.at(0).points.at(i).x *= 1.2;
        lowerhead.at(0).points.at(i).x += median;
        lowerhead.at(0).points.at(i).y -= top;
        lowerhead.at(0).points.at(i).y *= 0.5;
        lowerhead.at(0).points.at(i).y += top;
    }
    lowerhead.at(1).points.at(0).x -= median;
    lowerhead.at(1).points.at(0).x *= 1.2;
    lowerhead.at(1).points.at(0).x += median;
    lowerhead.at(1).points.at(0).y -= top;
    lowerhead.at(1).points.at(0).y *= 0.5;
    lowerhead.at(1).points.at(0).y += top;
    lowerhead.at(1).points.at(1).x -= median;
    lowerhead.at(1).points.at(1).x *= 1.2;
    lowerhead.at(1).points.at(1).x += median;
    lowerhead.at(1).points.at(1).y -= top;
    lowerhead.at(1).points.at(1).y *= 0.5;
    lowerhead.at(1).points.at(1).y += top;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x -= median;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x *= 1.2;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x += median;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y -= top;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y *= 0.5;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y += top;

    float bottom = 0;
    for (int i = 0; i < lowerhead.at(1).points.size(); i++){
        if (bottom < lowerhead.at(1).points.at(i).y)
            bottom = lowerhead.at(1).points.at(i).y;
    }
    for (int i = 0; i < lowerhead.at(1).points.size(); i++){
         if (bottom == lowerhead.at(1).points.at(i).y)
            lowerhead.at(1).points.at(i).y -= 2 * scale;
    }

    for (int i = 0; i < lowerhead.at(1).points.size() - 1; i++){
        if (bottom == lowerhead.at(1).points.at(i + 1).y){
            lowerhead.at(1).points.at(i).y -= 1 * scale;
            lowerhead.at(1).points.at(i).x -= 2 * scale;
        }
    }

    for (int i = lowerhead.at(1).points.size() - 1; i > 0; i--){
         if (bottom == lowerhead.at(1).points.at(i - 1).y){
            lowerhead.at(1).points.at(i).y -= 1 * scale;
            lowerhead.at(1).points.at(i).x += 2 * scale;
        }
    }
}

void LowerHead::sullen(float top, float width){
    lowerhead.clear();
    lowerhead.push_back(normal_state.at(0));
    lowerhead.push_back(normal_state.at(1));
    float min = 10000;
    float max = 0;
    float localtop = 10000;
    for (int i = 0; i < lowerhead.at(0).points.size(); i++){
        if (min > lowerhead.at(0).points.at(i).x)
            min = lowerhead.at(0).points.at(i).x;
        if (max < lowerhead.at(0).points.at(i).x)
            max = lowerhead.at(0).points.at(i).x;
        if (localtop > lowerhead.at(0).points.at(i).y)
            localtop = lowerhead.at(0).points.at(i).y;
    }
    float median = (min + max) / 2;
    //change lower lip
    for(int i = 0; i < lowerhead.at(0).points.size(); i++){
        lowerhead.at(0).points.at(i).x -= median;
        lowerhead.at(0).points.at(i).x *= 1.2;
        lowerhead.at(0).points.at(i).x += median;
        lowerhead.at(0).points.at(i).y -= top ;
        lowerhead.at(0).points.at(i).y *= 1.5 * abs(median - lowerhead.at(0).points.at(i).x) / width;
        lowerhead.at(0).points.at(i).y += top;
    }

    //change skin below lower lip
    lowerhead.at(1).points.at(0).x -= median;
    lowerhead.at(1).points.at(0).x *= 1.2;
    lowerhead.at(1).points.at(0).x += median;
    lowerhead.at(1).points.at(0).y -= top;
    lowerhead.at(1).points.at(0).y *= 1.5 * abs(median - lowerhead.at(1).points.at(0).x) / width;
    lowerhead.at(1).points.at(0).y += top;
    lowerhead.at(1).points.at(1).x -= median;
    lowerhead.at(1).points.at(1).x *= 1.2;
    lowerhead.at(1).points.at(1).x += median;
    lowerhead.at(1).points.at(1).y -= top;
    lowerhead.at(1).points.at(1).y *= 1.5 * abs(median - lowerhead.at(1).points.at(1).x) / width;
    lowerhead.at(1).points.at(1).y += top;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x -= median;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x *= 1.2;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x += median;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y -= top;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y *= 1.5 * abs(median - lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x) / width;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y += top;

    //change chin & cheeks
    float bottom = 0;
    for (int i = 0; i < lowerhead.at(1).points.size(); i++){
        if (bottom < lowerhead.at(1).points.at(i).y)
            bottom = lowerhead.at(1).points.at(i).y;
    }
    for (int i = 0; i < lowerhead.at(1).points.size(); i++){
         if (bottom == lowerhead.at(1).points.at(i).y)
            lowerhead.at(1).points.at(i).y -= 2 * scale;
    }

    for (int i = 0; i < lowerhead.at(1).points.size() - 1; i++){
        if (bottom == lowerhead.at(1).points.at(i + 1).y){
            lowerhead.at(1).points.at(i).y -= 1 * scale;
            lowerhead.at(1).points.at(i).x -= 2 * scale;
        }
    }
    for (int i = lowerhead.at(1).points.size() - 1; i > 0; i--){
         if (bottom == lowerhead.at(1).points.at(i - 1).y){
            lowerhead.at(1).points.at(i).y -= 1 * scale;
            lowerhead.at(1).points.at(i).x += 2 * scale;
        }
    }
}

void LowerHead::openMouth(float top, float width){
    lowerhead.clear();
    lowerhead.push_back(normal_state.at(0));
    lowerhead.push_back(normal_state.at(1));
    float min = 10000;
    float max = 0;
    int idxmin, idxmax;
    for (int i = 0; i < lowerhead.at(0).points.size(); i++){
        if (min > lowerhead.at(0).points.at(i).x){
            min = lowerhead.at(0).points.at(i).x;
            idxmin = i;
        }
        if (max < lowerhead.at(0).points.at(i).x){
            max = lowerhead.at(0).points.at(i).x;
            idxmax = i;
        }
    }
    float median = (min + max) / 2;

    for(int i = 0; i < lowerhead.at(0).points.size(); i++){
        lowerhead.at(0).points.at(i).x -= median;
        lowerhead.at(0).points.at(i).x *= 1.2;
        lowerhead.at(0).points.at(i).x += median;
        lowerhead.at(0).points.at(i).y -= top;
        if (i == idxmin || i == idxmax){
            lowerhead.at(0).points.at(i).y *= 0.5;
        }else{
            lowerhead.at(0).points.at(i).y += 5*scale;
        }
        lowerhead.at(0).points.at(i).y += top;
    }
    lowerhead.at(1).points.at(0).x -= median;
    lowerhead.at(1).points.at(0).x *= 1.2;
    lowerhead.at(1).points.at(0).x += median;
    lowerhead.at(1).points.at(0).y -= top;
    lowerhead.at(1).points.at(0).y += 5*scale;
    lowerhead.at(1).points.at(0).y += top;
    lowerhead.at(1).points.at(1).x -= median;
    lowerhead.at(1).points.at(1).x *= 1.2;
    lowerhead.at(1).points.at(1).x += median;
    lowerhead.at(1).points.at(1).y -= top;
    lowerhead.at(1).points.at(1).y *= 0.5;
    lowerhead.at(1).points.at(1).y += top;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x -= median;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x *= 1.2;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).x += median;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y -= top;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y *= 0.5;
    lowerhead.at(1).points.at(lowerhead.at(1).points.size() - 1).y += top;

    //find bottom
    float bottom = 0;
    for (int i = 0; i < lowerhead.at(1).points.size(); i++){
        if (bottom < lowerhead.at(1).points.at(i).y)
            bottom = lowerhead.at(1).points.at(i).y;
    }

    for (int i = 0; i < lowerhead.at(1).points.size(); i++){
         if (bottom == lowerhead.at(1).points.at(i).y)
            lowerhead.at(1).points.at(i).y += 4 * scale;
    }

    for (int i = 0; i < lowerhead.at(1).points.size() - 1; i++){
        if (bottom == lowerhead.at(1).points.at(i + 1).y){
            lowerhead.at(1).points.at(i).y += 2 * scale;
            lowerhead.at(1).points.at(i).x += 2 * scale;
        }
    }

    for (int i = lowerhead.at(1).points.size() - 1; i > 0; i--){
         if (bottom == lowerhead.at(1).points.at(i - 1).y){
            lowerhead.at(1).points.at(i).y += 2 * scale;
            lowerhead.at(1).points.at(i).x -= 2 * scale;
        }
    }
}