#ifndef __FACE
#define __FACE

#include "Point.h"
#include "Eyes.h"
#include "LowerHead.h"
#include "Shape.h"
#include <vector>
#include <map>
using namespace std;

class Face {
	public:
		//head 0, nose 1, upper lip 2
		vector<Shape> face;
		Eyes eyes;
		LowerHead lowerHead;
		float scale;
		vector<Shape > normal_state;

		Face();
		Face(map<string, vector<Point> > point, int a, int b, int c, float s);
		Face& operator=(const Face& f);
		void draw(ShadowBuffer& sb);
		void openMouth();
		void smile();

	protected:

	private:
};

#endif