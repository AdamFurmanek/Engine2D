#include "BoundingBox.h"

using namespace std;
/// Mechanizm gwarantuj�cy, �e podaj�c dowolne dwa przeciwleg�e punkty, "a" b�dzie oznacza� lewy g�rny, kiedy "c" b�dzie oznacza� prawy dolny r�g.
/// <param name="a">zmienna oznaczaj�ca lewy g�rny r�g</param>
/// <param name="c">zmienna oznaczaj�ca prawy dolny r�g</param>
BoundingBox::BoundingBox(Point2D a, Point2D c ){

	this->a = { (a.x < c.x) ? a.x : c.x, (a.y < c.y) ? a.y : c.y, a.c };
	this->c = { (a.x > c.x) ? a.x : c.x, (a.y > c.y) ? a.y : c.y, a.c };
	b = { this->c.x, this->a.y, this->a.c };
	d = { this->a.x, this->c.y, this->a.c };
}

/// Pobiera i zwraca warto��(wsp�rz�dne) zmiennej a
/// <returns>a</returns>
/// <param name="a">zmienna oznaczaj�ca lewy g�rny r�g</param>
Point2D BoundingBox::getA() {
	return a;
}
/// Pobiera i zwraca warto��(wsp�rz�dne) zmiennej c
/// <returns>c</returns>
/// <param name="c">zmienna oznaczaj�ca prawy dolny r�g</param>
Point2D BoundingBox::getC() {
	return c;
}
/// Pobiera i zwraca warto��(wsp�rz�dne) zmiennej b
/// <returns>b</returns>
/// <param name="b">zmienna oznaczaj�ca prawy g�rny r�g</param>
Point2D BoundingBox::getB() {
	return b;
}
/// Pobiera i zwraca warto��(wsp�rz�dne) zmiennej d
/// <returns>d</returns>
/// <param name="d">zmienna oznaczaj�ca lewy dolny r�g</param>
Point2D BoundingBox::getD() {
	return d;
}
/// Ustawienie wsp�rz�dnych na lewy g�rny r�g = a
/// <param name="a">zmienna oznaczaj�ca lewy g�rny r�g</param>
void BoundingBox::setA(Point2D a) {
	this->a = a;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}
/// Ustawienie wsp�rz�dnych na prawy dolny r�g = c
/// <param name="c">zmienna oznaczaj�ca prawy dolny r�g</param>
void BoundingBox::setC(Point2D c) {
	this->c = c;
	b = { c.x, a.y, a.c };
	d = { a.x, c.y, a.c };
}
/// Utworzenie wektora dwuwymiarowego points, dodaje elementy ko�cowe za pomoc� push_back kolejno a,b,c,d i zwraca wektor points
/// <returns>points</returns>
vector <Point2D> BoundingBox::getPoints() {
	vector <Point2D> points;
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	return points;
}
/// Typ logiczny zwracaj�cy true je�li wyst�puje kolizja, czyli boundigbox bb1 i bb2 na siebie zachodz�/nachodz� lub zwracaj�cy false w przeciwnym wypadku
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