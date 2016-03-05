#ifndef __EYES
#define __EYES
#define LEFT 0
#define RIGHT 1

#include "Point.h"
#include "Shape.h"
#include <vector>
using namespace std;

class Eyes {
	public:
		//right 0, left 1
		vector<Shape > eyebrows;
		vector<Shape > eyes;
		vector<Shape > eyeballs;
		vector<Shape > normal_state;
		float scale;
		Eyes();
		Eyes(vector <vector<Point > > points, int a, int b, int c, float s);
		Eyes& operator= (const Eyes& e);
		void draw(ShadowBuffer& sb);
		void wink(int side);
		//void winkLeft();
		void closeEyes();
		void stare();
		void normal();

	protected:

	private:
};

#endif