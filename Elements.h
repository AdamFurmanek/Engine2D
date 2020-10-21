#ifndef Elements_h
#define Elements_h

#include "Engine.h"

using namespace std;

struct Point2D {
	double x;
	double y;
	ALLEGRO_COLOR c;
};

class LineSegment {
private:
	Point2D a;
	Point2D b;
	ALLEGRO_COLOR c;
public:
	LineSegment(Point2D a, Point2D b, ALLEGRO_COLOR c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Point2D getA() {
		return a;
	}

	Point2D getB() {
		return b;
	}
	ALLEGRO_COLOR getC() {
		return c;
	}

	void setA(Point2D a) {
		this->a = a;
	}

	void setB(Point2D b) {
		this->b = b;
	}

	void setC(ALLEGRO_COLOR c) {
		this->c=c;
	}

};

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