#ifndef BoundingBox_h
#define BoundingBox_h

#include "Point2D.h"
#include "Enums.h"
#include <vector>

using namespace std;

class BoundingBox
{
private:
	Point2D a, b, c, d;
public:
	BoundingBox(Point2D a = { 0,0,Black }, Point2D c = { 0,0,Black });
	Point2D getA();
	Point2D getC();
	Point2D getB();
	Point2D getD();
	void setA(Point2D a);
	void setC(Point2D c);
	vector <Point2D> getPoints();
	static bool Colission(BoundingBox bb1, BoundingBox bb2);
};
#endif
