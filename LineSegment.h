#ifndef LineSegment_h
#define LineSegment_h

#include "Point2D.h"

using namespace std;
class LineSegment {
private:
	Point2D a;
	Point2D b;
	ALLEGRO_COLOR c;
public:
	LineSegment(Point2D a, Point2D b, ALLEGRO_COLOR c);
	Point2D getA();
	Point2D getB();
	ALLEGRO_COLOR getC();
	void setA(Point2D a);
	void setB(Point2D b);
	void setC(ALLEGRO_COLOR c);

};

#endif