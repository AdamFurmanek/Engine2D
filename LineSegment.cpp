#include "LineSegment.h"
/// Inicjacja punktów i koloru LineSegment
/// <param name="a">wspó³rzêdna a(x)</param>
/// <param name="b">wspó³rzêdna b(y)</param>
/// <param name="c">kolor</param>
LineSegment::LineSegment(Point2D a, Point2D b, ALLEGRO_COLOR c) {
	this->a = a;
	this->b = b;
	this->c = c;
}
/// Pobranie punktu A
/// <returns>a</returns>
Point2D LineSegment::getA() {
	return a;
}
/// Pobranie punktu B
/// <returns>b</returns>
Point2D LineSegment::getB() {
	return b;
}
/// Pobranie koloru
/// <returns>c</returns>
ALLEGRO_COLOR LineSegment::getC() {
	return c;
}
/// Ustawienie punktu A
/// <param name="a">wspó³rzêdna a(x)</param>
void LineSegment::setA(Point2D a) {
	this->a = a;
}
/// Ustawienie punktu B
/// <param name="b">wspó³rzêdna b(y)</param>
void LineSegment::setB(Point2D b) {
	this->b = b;
}
/// Ustawienie koloru
/// <param name="c">kolor</param>
void LineSegment::setC(ALLEGRO_COLOR c) {
	this->c = c;
}