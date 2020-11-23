#include "ShapeCircle.h"
/// Inicjacja punktu i promienia ShapeCircle
/// <param name="point">zmienna okreœlaj¹ca œrodek ko³a</param>
/// <param name="radius">zmienna okreœlaj¹ca promieñ ko³a</param>
ShapeCircle::ShapeCircle(Point2D point, double radius) : Shape() {
	this->point = point;
	this->radius = radius;
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}
/// Funkcja rysuj¹ca ko³o
/// <param name="buffer"> g³ówny bitmapa(okienko ekranu)</param>
void ShapeCircle::Draw(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawCircle(point, radius, true);
}
/// Funkcja pokazuj¹ca granice kolizji
/// <param name="buffer">g³ówna bitmapa(okienko ekranu)</param>
void ShapeCircle::DrawBoundingBox(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawLineSegment(bb.getPoints(), false);
}
/// Funkcja zwracaj¹ca granice kolizji (obiekt BoundingBox)
/// <returns>bb</returns>
BoundingBox ShapeCircle::GetBoundingBox() {
	return bb;
}
/// Typ logiczny zwracaj¹cy prawdê je¿eli kolizja wystêpuje, lub fa³sz w przeciwnym wypadku
/// <param name="bb2"></param>
/// <returns>true/false</returns>
bool ShapeCircle::Collison(BoundingBox bb2) {
	if(bb2.Colission(bb2,bb))
		return true;
	return false;
}
/// Translacja o wektor
/// <param name="x"></param>
/// <param name="y"></param>
void ShapeCircle::VectorTranslation(double x, double y) {
	point.x += x;
	point.y += y;
	bb.setA({ bb.getA().x + x,bb.getA().y + y,bb.getA().c });
	bb.setC({ bb.getC().x + x,bb.getC().y + y,bb.getC().c });
}
/// Obrót ko³a
/// <param name="alfa"></param>
/// <param name="p"></param>
void ShapeCircle::Rotate(double alfa, Point2D p) {
	point.x = p.x + (point.x - p.x) * cos(alfa) - (point.y - p.y) * sin(alfa);
	point.y = p.y + (point.x - p.x) * sin(alfa) - (point.y - p.y) * cos(alfa);
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}
/// Skalowanie ko³a
/// <param name="kx">wspó³czynnik skalowania wspó³rzêdnej x</param>
/// <param name="ky">wspó³czynnik skalowania wspó³rzêdnej y</param>
/// <param name="p">?</param>
void ShapeCircle::Scaling(double kx, double ky, Point2D p) {
	point.x = point.x * kx + (1 - kx) * p.x;
	point.y = point.y * ky + (1 - ky) * p.y;
	radius = radius * ky * kx;
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}