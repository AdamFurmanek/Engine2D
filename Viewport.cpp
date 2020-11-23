#include "Viewport.h"

using namespace std;

/// Mechanizm gwarantuj¹cy, ¿e podaj¹c dowolne dwa przeciwleg³ê punkty, "a" bêdzie oznacza³ lewy górny, kiedy "c" bêdzie oznacza³ prawy dolny róg.
/// <param name="a">zmienna odpowiadaj¹ca lewemu górnemu rogowi</param>
/// <param name="c">zmienna odpowiadaj¹ca prawemu dolnemu rogowi</param>
Viewport::Viewport(Point2D a, Point2D c) {
	this->a = { (a.x < c.x) ? a.x : c.x, (a.y < c.y) ? a.y : c.y, a.c };
	this->c = { (a.x > c.x) ? a.x : c.x, (a.y > c.y) ? a.y : c.y, a.c };
	b = { this->c.x, this->a.y, this->a.c };
	d = { this->a.x, this->c.y, this->a.c };
}
/// Pobranie wspó³rzêdnej punktu A
/// <returns>a</returns>
Point2D Viewport::getA() {
	return a;
}
/// Pobranie wspó³rzêdnej punktu B
/// <returns>b</returns>
Point2D Viewport::getB() {
	return b;
}
/// Pobranie wszystkich punktów w tablicy
/// <returns>points</returns>
vector <Point2D> Viewport::getPoints() {
	vector <Point2D> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	return points;
}
/// Ustawienie wspó³rzêdnych punktu A
/// <param name="a">zmienna odpowiadaj¹ca lewemu górnemu rogowi</param>
void Viewport::setA(Point2D a) {
	this->a = a;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}
/// Ustawienie wspó³rzêdnych punktu B
/// <param name="c">zmienna odpowiadaj¹ca prawemu dolnemu rogowi</param>
void Viewport::setC(Point2D c) {
	this->c = c;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}
/// Funcja odpowiadaj¹ca za ruch gracza
/// <param name="dr"> kierunek poruszani</param>
/// <param name="pixels"></param>
void Viewport::move(direction dr, int pixels) {

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
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}

/// Zwraca tablicê uciêtych odcinków
/// <param name="ls"></param>
/// <returns>ls</returns>
vector <LineSegment> Viewport::cut(vector <LineSegment> ls) {
	for (int i = 0; i < ls.size();i++) {
		ls[i] = cut(ls[i]);
	}
	return ls;
}
/// zwraca uciêty odcinek
/// <param name="ls"></param>
/// <returns>ls</returns>
LineSegment Viewport::cut(LineSegment ls) {

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
			return { { 0, 0, NULL }, { 0, 0, NULL }, ls.getC() };
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

		ls = { { x1, y1, NULL }, { x2, y2, NULL }, ls.getC() };
	}
	return ls;
}