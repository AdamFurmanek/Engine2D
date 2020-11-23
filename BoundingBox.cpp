#include "BoundingBox.h"

using namespace std;
/// Mechanizm gwarantuj¹cy, ¿e podaj¹c dowolne dwa przeciwleg³e punkty, "a" bêdzie oznacza³ lewy górny, kiedy "c" bêdzie oznacza³ prawy dolny róg.
/// <param name="a">zmienna oznaczaj¹ca lewy górny róg</param>
/// <param name="c">zmienna oznaczaj¹ca prawy dolny róg</param>
BoundingBox::BoundingBox(Point2D a, Point2D c ){

	this->a = { (a.x < c.x) ? a.x : c.x, (a.y < c.y) ? a.y : c.y, a.c };
	this->c = { (a.x > c.x) ? a.x : c.x, (a.y > c.y) ? a.y : c.y, a.c };
	b = { this->c.x, this->a.y, this->a.c };
	d = { this->a.x, this->c.y, this->a.c };
}

/// Pobiera i zwraca wartoœæ(wspó³rzêdne) zmiennej a
/// <returns>a</returns>
/// <param name="a">zmienna oznaczaj¹ca lewy górny róg</param>
Point2D BoundingBox::getA() {
	return a;
}
/// Pobiera i zwraca wartoœæ(wspó³rzêdne) zmiennej c
/// <returns>c</returns>
/// <param name="c">zmienna oznaczaj¹ca prawy dolny róg</param>
Point2D BoundingBox::getC() {
	return c;
}
/// Pobiera i zwraca wartoœæ(wspó³rzêdne) zmiennej b
/// <returns>b</returns>
/// <param name="b">zmienna oznaczaj¹ca prawy górny róg</param>
Point2D BoundingBox::getB() {
	return b;
}
/// Pobiera i zwraca wartoœæ(wspó³rzêdne) zmiennej d
/// <returns>d</returns>
/// <param name="d">zmienna oznaczaj¹ca lewy dolny róg</param>
Point2D BoundingBox::getD() {
	return d;
}
/// Ustawienie wspó³rzêdnych na lewy górny róg = a
/// <param name="a">zmienna oznaczaj¹ca lewy górny róg</param>
void BoundingBox::setA(Point2D a) {
	this->a = a;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}
/// Ustawienie wspó³rzêdnych na prawy dolny róg = c
/// <param name="c">zmienna oznaczaj¹ca prawy dolny róg</param>
void BoundingBox::setC(Point2D c) {
	this->c = c;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}
/// Utworzenie wektora dwuwymiarowego points, dodaje elementy koñcowe za pomoc¹ push_back kolejno a,b,c,d i zwraca wektor points
/// <returns>points</returns>
vector <Point2D> BoundingBox::getPoints() {
	vector <Point2D> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	return points;
}
/// Typ logiczny zwracaj¹cy true jeœli wystêpuje kolizja, czyli boundigbox bb1 i bb2 na siebie zachodz¹/nachodz¹ lub zwracaj¹cy false w przeciwnym wypadku
/// <param name="bb1">BoundingBox nr1</param>
/// <param name="bb2">BoundingBox nr2</param>
/// <returns>true/false</returns>
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