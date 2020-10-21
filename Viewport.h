#ifndef Viewport_h
#define Viewport_h

#include "Point2D.h"
#include <vector>
#include "Enums.h"
#include "LineSegment.h"

using namespace std;

class Viewport {
private:
	Point2D a, b, c, d;
public:
	/* Konstruktor przyjmuje dwa przeciwleg³e punkty prostok¹ta. */
	Viewport(Point2D a, Point2D c);
	Point2D getA();
	Point2D getB();
	vector <Point2D> getPoints();
	void setA(Point2D a);
	void setC(Point2D c);
	void move(direction dr, int pixels);
	vector <LineSegment> cut(vector <LineSegment> ls);
	LineSegment cut(LineSegment ls);
};

#endif