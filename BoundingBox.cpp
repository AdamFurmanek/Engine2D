#include "BoundingBox.h"

using namespace std;

BoundingBox::BoundingBox(Point2D a, Point2D c ){
	/* Mechanizm gwarantuj¹cy, ¿e podaj¹c dowolne dwa przeciwleg³ê punkty, "a" bêdzie oznacza³ lewy górny, kiedy "c" bêdzie oznacza³ prawy dolny róg. */
	this->a = { (a.x < c.x) ? a.x : c.x, (a.y < c.y) ? a.y : c.y, a.c };
	this->c = { (a.x > c.x) ? a.x : c.x, (a.y > c.y) ? a.y : c.y, a.c };
	b = { this->c.x, this->a.y, this->a.c };
	d = { this->a.x, this->c.y, this->a.c };
}

Point2D BoundingBox::getA() {
	return a;
}

Point2D BoundingBox::getC() {
	return c;
}

Point2D BoundingBox::getB() {
	return b;
}

Point2D BoundingBox::getD() {
	return d;
}

void BoundingBox::setA(Point2D a) {
	this->a = a;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}

void BoundingBox::setC(Point2D c) {
	this->c = c;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}

vector <Point2D> BoundingBox::getPoints() {
	vector <Point2D> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	return points;
}

bool BoundingBox::Colission(BoundingBox bb1, BoundingBox bb2) {
	if (bb1.getA().x >= bb2.getA().x && bb1.getA().x <= bb2.getC().x && bb1.getA().y >= bb2.getA().y && bb1.getA().y <= bb2.getC().y
		|| bb1.getB().x >= bb2.getA().x && bb1.getB().x <= bb2.getC().x && bb1.getB().y >= bb2.getA().y && bb1.getB().y <= bb2.getC().y
		|| bb1.getC().x >= bb2.getA().x && bb1.getC().x <= bb2.getC().x && bb1.getC().y >= bb2.getA().y && bb1.getC().y <= bb2.getC().y
		|| bb1.getD().x >= bb2.getA().x && bb1.getD().x <= bb2.getC().x && bb1.getD().y >= bb2.getA().y && bb1.getD().y <= bb2.getC().y
		) {
		return true;
	}
	return false;
}