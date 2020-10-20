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

enum direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Viewport {
private:
	Point2D a, b, c, d;
public:
	/* Konstruktor przyjmuje dwa przeciwleg³e punkty prostok¹ta. */
	Viewport(Point2D a, Point2D c) {
		this->a = a;
		this->c = c;
		update();

	}
	Point2D getA() {
		return a;
	}
	Point2D getB() {
		return b;
	}

	vector <Point2D> getPoints() {
		vector <Point2D> points;
		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);
		return points;
	}

	void setA(Point2D a) {
		this->a = a;
		update();
	}
	void setC(Point2D c) {
		this->c = c;
		update();
	}

	void move(direction dr, int pixels) {

		switch (dr) {
		case UP:
			a.y -= pixels;
			c.y -= pixels;
			break;
		case RIGHT:
			a.x += pixels;
			c.x += pixels;
			break;
		case DOWN:
			a.y += pixels;
			c.y += pixels;
			break;
		case LEFT:
		default:
			a.x -= pixels;
			c.x -= pixels;
			break;
		}
		update();
	}

	void update() {
		b = { c.x, a.y, a.c };
		d = { a.x, c.y, a.c };
	}

	vector <LineSegment> cut(vector <LineSegment> ls) {
		for (int i = 0; i < ls.size();i++) {
			ls[i]=cut(ls[i]);
		}
		return ls;
	}

	LineSegment cut(LineSegment ls) {

		double x1, y1, x2, y2;

		for (int i = 0;i < 2;i++) {
			x1 = ls.getA().x;
			y1 = ls.getA().y;
			x2 = ls.getB().x;
			y2 = ls.getB().y;

			bool kodA[4] = { 0,0,0,0 };
			bool kodB[4] = { 0,0,0,0 };

			if (x1 < a.x) kodA[0] = 1;
			if (y1 < a.y) kodA[1] = 1;
			if (x1 > c.x) kodA[2] = 1;
			if (y1 > c.y) kodA[3] = 1;

			if (x2 < a.x) kodB[0] = 1;
			if (y2 < a.y) kodB[1] = 1;
			if (x2 > c.x) kodB[2] = 1;
			if (y2 > c.y) kodB[3] = 1;

			if (!kodA[0] && !kodA[1] && !kodA[2] && !kodA[3] && !kodB[0] && !kodB[1] && !kodB[2] && !kodB[3]) {
				return ls;
			}
			if ((kodA[0] && kodB[0]) || (kodA[1] && kodB[1]) || (kodA[2] && kodB[2]) || (kodA[3] && kodB[3])) {
				return { { 0, 0, NULL }, { 0, 0, NULL }, al_map_rgb(100, 255, 100) };
			}

			if (!kodA[0] && !kodA[1] && !kodA[2] && !kodA[3]) {

				bool temporary;
				for (int i = 0; i < 4;i++) {
					temporary = kodA[i];
					kodA[i] = kodB[i];
					kodB[i] = temporary;
				}

				int temporary1 = x1;
				x1 = x2;
				x2 = temporary1;
				int temporary2 = y1;
				y1 = y2;
				y2 = temporary2;

			}
			if (kodA[0] == 1) {
				y1 = y1 + (a.x - x1) * (y2 - y1) / (x2 - x1);
				x1 = a.x;
			}
			if (kodA[1] == 1) {
				x1 = x1 + (a.y - y1) * (x2 - x1) / (y2 - y1);
				y1 = a.y;
			}
			if (kodA[2] == 1) {
				y1 = y1 + (c.x - x1) * (y2 - y1) / (x2 - x1);
				x1 = c.x;
			}
			if (kodA[3] == 1) {
				x1 = x1 + (c.y - y1) * (x2 - x1) / (y2 - y1);
				y1 = c.y;
			}

			ls = { { x1, y1, NULL }, { x2, y2, NULL }, al_map_rgb(100, 255, 100) };
		}
			return ls;
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

