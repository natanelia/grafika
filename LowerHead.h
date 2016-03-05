#ifndef __LOWERHEAD
#define __LOWERHEAD

#include "Point.h"
#include "Shape.h"
#include <vector>
using namespace std;

class LowerHead {
	public:
		//lowerlip 0, jaw 1
		vector<Shape> lowerhead;
		vector<Shape> normal_state;
		float scale;

		LowerHead();
		LowerHead(vector <vector<Point > > points, int a, int b, int c, float s);
		LowerHead& operator= (const LowerHead& lh);
		void draw(ShadowBuffer& sb);
		void smile(float top);

	protected:

	private:
};

#endif