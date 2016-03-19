#include "ImageGroup.h"
#include <string>


using namespace std;

ImageGroup::ImageGroup(string filename, string posname, float offsetX, float offsetY, int scale) {
	ColorTable ct("assets/ColorTable.ct");
	Util util;
	for (int i=1; i<=40; i++) {
		ostringstream ss;
    	ss << i;

		string iString = ss.str();
		string nama = filename + "-" + iString + ".txt";
		Image label = util.convertImageFile(nama, ct);
		images.push_back(label);
		
	}
	insertPosition(posname, offsetX, offsetY, scale);
	
}

void ImageGroup::insertPosition(string filename, int offsetX, int offsetY, int scale){
	Util util;
	map<string, vector<Point> > pos = util.readObject(filename);
	vector<Point> points = pos.find("Position")->second;
	cout << "size" << points.size();
	for (int i=0; i<images.size(); i++) {
		Point p(points[i].x * scale + offsetX, points[i].y * scale + offsetY, 0);
		images[i].position=p;
		images[i].translate(p.x,p.y,0);
	}
}

void ImageGroup::draw(ShadowBuffer& sb) {
	for(int i=0; i<images.size(); i++) {

		images[i].draw(sb);
	}
}

void ImageGroup::translate(float dX, float dY,float dZ){
	for(int i=0; i<images.size(); i++) {
		images[i].translate(dX,dY,0);
	}
}

void ImageGroup::rotatePositionX(float degree, float offsetX, float offsetY, float offsetZ){
	for (int i=0; i<images.size();i++){
		Point temp = images[i].position;
		temp.translation(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
		temp.rotateX(degree);

		//pembulatan
             temp.setX(roundf(temp.x * 100) / 100);
             temp.setY(roundf(temp.y * 100) / 100);
             temp.setZ(roundf(temp.z * 100) / 100);


        temp.translation(offsetX,offsetY, offsetZ);
        images[i].setPosition(temp);
	}

}

void ImageGroup::rotatePositionY(float degree, float offsetX, float offsetY, float offsetZ){
		
		for (int i=0; i<images.size();i++){
		Point temp = images[i].position;	
		temp.translation(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
		temp.rotateY(degree);

		//pembulatan
             temp.setX(roundf(temp.x * 100) / 100);
             temp.setY(roundf(temp.y * 100) / 100);
             temp.setZ(roundf(temp.z * 100) / 100);


        temp.translation(offsetX,offsetY, offsetZ);
        images[i].setPosition(temp);
	}
}

void ImageGroup::rotatePositionZ(float degree, float offsetX, float offsetY, float offsetZ){
	for (int i=0; i<images.size();i++){
		Point temp = images[i].position;
		temp.translation(offsetX*(-1),offsetY*(-1), offsetZ*(-1));
		temp.rotateZ(degree);

		//pembulatan
             temp.setX(roundf(temp.x * 100) / 100);
             temp.setY(roundf(temp.y * 100) / 100);
             temp.setZ(roundf(temp.z * 100) / 100);


        temp.translation(offsetX,offsetY, offsetZ);
        images[i].setPosition(temp);
	}
}

void ImageGroup::translatePos(float offsetX, float offsetY, float offsetZ){
	for (int i=0; i<images.size();i++){
		
		images[i].position.translation(offsetX,offsetY,offsetZ);
		if (offsetZ!=0){
			images[i].project2dPos();
		} else{
			images[i].translate(offsetX,offsetY,offsetZ);
		}
	}
}

