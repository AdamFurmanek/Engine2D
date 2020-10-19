#include "Engine.h"
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
};

class Drawer
{
private:
	ALLEGRO_BITMAP* buffer;
public:
	Drawer(ALLEGRO_BITMAP* buffer);

	void Clear();
	void DrawPixels(vector <Point2D> pixels);
	void DrawTriangle(Point2D a, Point2D b, Point2D c, ALLEGRO_COLOR co);
	void DrawLineSegment(LineSegment lineSegment);
	void DrawLineSegment(vector <LineSegment> lineSegment);
	void DrawLineSegment(vector <Point2D> pixels, bool open);

};

