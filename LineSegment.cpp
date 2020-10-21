#include "LineSegment.h"

LineSegment::LineSegment(Point2D a, Point2D b, ALLEGRO_COLOR c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Point2D LineSegment::getA() {
	return a;
}

Point2D LineSegment::getB() {
	return b;
}
ALLEGRO_COLOR LineSegment::getC() {
	return c;
}

void LineSegment::setA(Point2D a) {
	this->a = a;
}

void LineSegment::setB(Point2D b) {
	this->b = b;
}

void LineSegment::setC(ALLEGRO_COLOR c) {
	this->c = c;
}