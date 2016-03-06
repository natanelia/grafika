#include "Eyes.h"


Eyes::Eyes(){}

Eyes::Eyes(vector<vector<Point > > points, int a, int b, int c, float s){
	Color color;
	scale = s;

	//right eyebrow
	Shape right_eyebrow(points.at(0));
	color = Color((int)points[0][points[0].size() - 1].x,(int)points[0][points[0].size() - 1].y,(int)points[0][points[0].size() - 1].z);
	right_eyebrow.setColor(color);
	right_eyebrow.points.erase(right_eyebrow.points.begin() + right_eyebrow.points.size() - 1);
	for (int i = 0; i < right_eyebrow.points.size(); i++){
		right_eyebrow.points.at(i).x *= scale;
		right_eyebrow.points.at(i).x += a;
		right_eyebrow.points.at(i).y *= scale;
		right_eyebrow.points.at(i).y += b;
		right_eyebrow.points.at(i).z *= scale;
		right_eyebrow.points.at(i).z += c;
	}
	eyebrows.push_back(right_eyebrow);
	normal_state.push_back(right_eyebrow);

	//left eyebrow
	Shape left_eyebrow(points.at(1));
	color = Color((int)points[1][points[1].size() - 1].x,(int)points[1][points[1].size() - 1].y,(int)points[1][points[1].size() - 1].z);
	left_eyebrow.setColor(color);
	left_eyebrow.points.erase(left_eyebrow.points.begin() + left_eyebrow.points.size() - 1);
	for (int i = 0; i < left_eyebrow.points.size(); i++){
		left_eyebrow.points.at(i).x *= scale;
		left_eyebrow.points.at(i).x += a;
		left_eyebrow.points.at(i).y *= scale;
		left_eyebrow.points.at(i).y += b;
		left_eyebrow.points.at(i).z *= scale;
		left_eyebrow.points.at(i).z += c;
	}
	eyebrows.push_back(left_eyebrow);
	normal_state.push_back(left_eyebrow);

	//right eye
	Shape right_eye(points.at(2));
	color = Color((int)points[2][points[2].size() - 1].x,(int)points[2][points[2].size() - 1].y,(int)points[2][points[2].size() - 1].z);
	right_eye.setColor(color);
	right_eye.points.erase(right_eye.points.begin() + right_eye.points.size() - 1);
	for (int i = 0; i < right_eye.points.size(); i++){
		right_eye.points.at(i).x *= scale;
		right_eye.points.at(i).x += a;
		right_eye.points.at(i).y *= scale;
		right_eye.points.at(i).y += b;
		right_eye.points.at(i).z *= scale;
		right_eye.points.at(i).z += c;
	}
	eyes.push_back(right_eye);
	normal_state.push_back(right_eye);

	//left eye
	Shape left_eye(points.at(3));
	color = Color((int)points[3][points[3].size() - 1].x,(int)points[3][points[3].size() - 1].y,(int)points[3][points[3].size() - 1].z);
	left_eye.setColor(color);
	left_eye.points.erase(left_eye.points.begin() + left_eye.points.size() - 1);
	for (int i = 0; i < left_eye.points.size(); i++){
		left_eye.points.at(i).x *= scale;
		left_eye.points.at(i).x += a;
		left_eye.points.at(i).y *= scale;
		left_eye.points.at(i).y += b;
		left_eye.points.at(i).z *= scale;
		left_eye.points.at(i).z += c;
	}
	eyes.push_back(left_eye);
	normal_state.push_back(left_eye);

	//right eyeball
	Shape right_eyeball(points.at(4));
	color = Color((int)points[4][points[4].size() - 1].x,(int)points[4][points[4].size() - 1].y,(int)points[4][points[4].size() - 1].z);
	right_eyeball.setColor(color);
	right_eyeball.points.erase(right_eyeball.points.begin() + right_eyeball.points.size() - 1);
	for (int i = 0; i < right_eyeball.points.size(); i++){
		right_eyeball.points.at(i).x *= scale;
		right_eyeball.points.at(i).x += a;
		right_eyeball.points.at(i).y *= scale;
		right_eyeball.points.at(i).y += b;
		right_eyeball.points.at(i).z *= scale;
		right_eyeball.points.at(i).z += c;
	}
	eyeballs.push_back(right_eyeball);
	normal_state.push_back(right_eyeball);

	//left eyeball
	Shape left_eyeball(points.at(5));
	color = Color((int)points[5][points[5].size() - 1].x,(int)points[5][points[5].size() - 1].y,(int)points[5][points[5].size() - 1].z);
	left_eyeball.setColor(color);
	left_eyeball.points.erase(left_eyeball.points.begin() + left_eyeball.points.size() - 1);
	for (int i = 0; i < left_eyeball.points.size(); i++){
		left_eyeball.points.at(i).x *= scale;
		left_eyeball.points.at(i).x += a;
		left_eyeball.points.at(i).y *= scale;
		left_eyeball.points.at(i).y += b;
		left_eyeball.points.at(i).z *= scale;
		left_eyeball.points.at(i).z += c;
	}
	eyeballs.push_back(left_eyeball);
	normal_state.push_back(left_eyeball);
}

Eyes& Eyes::operator= (const Eyes& e){
	this->eyebrows = e.eyebrows;
	this->eyes = e.eyes;
	this->eyeballs = e.eyeballs;
	this->normal_state = e.normal_state;
	this->scale = e.scale;
	return *this;
}

void Eyes::draw(ShadowBuffer& sb){
	eyebrows.at(LEFT).draw(sb);
	eyebrows.at(RIGHT).draw(sb);
	eyes.at(LEFT).draw(sb);
	eyes.at(RIGHT).draw(sb);
	//eyeballs.at(LEFT).draw(sb);
	//eyeballs.at(RIGHT).draw(sb);	
	eyeballs.at(LEFT).scanLineIntersect(sb,eyes.at(LEFT));
	eyeballs.at(RIGHT).scanLineIntersect(sb,eyes.at(RIGHT));
}

void Eyes::wink(int side){
	eyebrows.clear();
	eyes.clear();
	eyeballs.clear();
	eyebrows.push_back(normal_state.at(0));
	eyebrows.push_back(normal_state.at(1));
	eyes.push_back(normal_state.at(2));
	eyes.push_back(normal_state.at(3));
	eyeballs.push_back(normal_state.at(4));
	eyeballs.push_back(normal_state.at(5));
	int i = 1;
	while(eyes.at(side).points.at(i).tag != 0){
		eyes.at(side).points.at(i).y += 2.5 * scale;
		i++;
	}
}

// void Eyes::winkLeft(){
// 	eyebrows.clear();
// 	eyes.clear();
// 	eyeballs.clear();
// 	eyebrows.push_back(normal_state.at(0));
// 	eyebrows.push_back(normal_state.at(1));
// 	eyes.push_back(normal_state.at(2));
// 	eyes.push_back(normal_state.at(3));
// 	eyeballs.push_back(normal_state.at(4));
// 	eyeballs.push_back(normal_state.at(5));
// 	int i = 1;
// 	while(eyes.at(1).points.at(i).tag != 0){
// 		eyes.at(1).points.at(i).y += 2.5 * scale;
// 		i++;
// 	}
// }

void Eyes::closeEyes(){
	eyes.clear();
	eyes.push_back(normal_state.at(2));
	eyes.push_back(normal_state.at(3));
	eyes.at(LEFT).color= Color(0,0,0);
	eyes.at(RIGHT).color= Color(0,0,0);
	int i = 1;
	while(eyes.at(0).points.at(i).tag != 0){
		eyes.at(0).points.at(i).y += 2.5 * scale;
		i++;
	}
	i = 1;
	while(eyes.at(1).points.at(i).tag != 0){
		eyes.at(1).points.at(i).y += 2.5 * scale;
		i++;
	}
}

void Eyes::happyEyes(){
	eyes.clear();
	eyes.push_back(normal_state.at(2));
	eyes.push_back(normal_state.at(3));
	eyes.at(LEFT).color= Color(0,0,0);
	eyes.at(RIGHT).color= Color(0,0,0);
	int i = eyes.at(0).points.size() - 1;
	while(eyes.at(0).points.at(i).tag != 0){
		eyes.at(0).points.at(i).y -= 3 * scale;
		i--;
	}
	i = eyes.at(1).points.size() - 1;
	while(eyes.at(1).points.at(i).tag != 0){
		eyes.at(1).points.at(i).y -= 3 * scale;
		i--;
	}
}

void Eyes::stare(){
	eyebrows.clear();
	eyes.clear();
	eyebrows.push_back(normal_state.at(0));
	eyebrows.push_back(normal_state.at(1));
	eyes.push_back(normal_state.at(2));
	eyes.push_back(normal_state.at(3));
	int i = 1;
	while(eyes.at(0).points.at(i).tag != 0){
		eyes.at(0).points.at(i).y -= 1 * scale;
		i++;
	}
	eyes.at(0).points.at(i).y -= 1 * scale;
	i = 1;
	while(eyes.at(1).points.at(i).tag != 0){
		eyes.at(1).points.at(i).y -= 1 * scale;
		i++;
	}
	eyes.at(1).points.at(i).y -= 1 * scale;
	i = 0;
	while(eyebrows.at(0).points.at(i).tag == 0){
		eyebrows.at(0).points.at(i).y += 1 * scale;
		i++;
	}
	for (int j = i; j < eyebrows.at(0).points.size(); j++){
		eyebrows.at(0).points.at(j).y -= 1 * scale;
	}
	i = 0;
	while(eyebrows.at(1).points.at(i).tag == 0){
		eyebrows.at(1).points.at(i).y += 1 * scale;
		i++;
	}
	for (int j = i; j < eyebrows.at(1).points.size(); j++){
		eyebrows.at(1).points.at(j).y -= 1 * scale;
	}
}

void Eyes::eyebrowUp(int side, float scale){
	eyebrows.clear();
	eyebrows.push_back(normal_state.at(0));
	eyebrows.push_back(normal_state.at(1));

	if (side == 2){
		eyebrows.at(0).rotate(eyebrows.at(0).points.at(0),-35);
		for(int i = 0; i < eyebrows.at(0).points.size(); i++){
			eyebrows.at(0).translate(0,-1*scale);
		}

		eyebrows.at(1).rotate(eyebrows.at(1).points.at(0),35);
		for(int i = 0; i < eyebrows.at(1).points.size(); i++){
			eyebrows.at(1).translate(0,-1*scale);
		}
	}else{
		eyebrows.at(side).rotate(eyebrows.at(side).points.at(0),-35 + 70 * side);
		for(int i = 0; i < eyebrows.at(side).points.size(); i++){
			eyebrows.at(side).translate(0,-1*scale);
		}
	}
}

void Eyes::eyebrowDown(int side, float scale){
	eyebrows.clear();
	eyebrows.push_back(normal_state.at(0));
	eyebrows.push_back(normal_state.at(1));

	if (side == 2){
		eyebrows.at(0).rotate(eyebrows.at(0).points.at(0),15);
		for(int i = 0; i < eyebrows.at(0).points.size(); i++){
			eyebrows.at(0).translate(0,+0.5*scale);
		}

		eyebrows.at(1).rotate(eyebrows.at(1).points.at(0),-15);
		for(int i = 0; i < eyebrows.at(1).points.size(); i++){
			eyebrows.at(1).translate(0,+0.5*scale);
		}
	}else{
		eyebrows.at(side).rotate(eyebrows.at(side).points.at(0),15 - 30 * side);
		for(int i = 0; i < eyebrows.at(side).points.size(); i++){
			eyebrows.at(side).translate(0,+0.5*scale);
		}
	}
}

void Eyes::normal(){
	eyebrows.clear();
	eyes.clear();
	eyeballs.clear();
	eyebrows.push_back(normal_state.at(0));
	eyebrows.push_back(normal_state.at(1));
	eyes.push_back(normal_state.at(2));
	eyes.push_back(normal_state.at(3));
	eyeballs.push_back(normal_state.at(4));
	eyeballs.push_back(normal_state.at(5));
}