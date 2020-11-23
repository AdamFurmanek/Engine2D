#include "ShapeCircle.h"
/// Inicjacja punktu i promienia ShapeCircle
/// <param name="point">zmienna okre�laj�ca �rodek ko�a</param>
/// <param name="radius">zmienna okre�laj�ca promie� ko�a</param>
ShapeCircle::ShapeCircle(Point2D point, double radius) : Shape() {
	this->point = point;
	this->radius = radius;
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}
/// Funkcja rysuj�ca ko�o
/// <param name="buffer"> g��wny bitmapa(okienko ekranu)</param>
void ShapeCircle::Draw(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawCircle(point, radius, true);
}
/// Funkcja pokazuj�ca granice kolizji
/// <param name="buffer">g��wna bitmapa(okienko ekranu)</param>
void ShapeCircle::DrawBoundingBox(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawLineSegment(bb.getPoints(), false);
}
/// Funkcja zwracaj�ca granice kolizji (obiekt BoundingBox)
/// <returns>bb</returns>
BoundingBox ShapeCircle::GetBoundingBox() {
	return bb;
}
/// Typ logiczny zwracaj�cy prawd� je�eli kolizja wyst�puje, lub fa�sz w przeciwnym wypadku
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
/// Obr�t ko�a
/// <param name="alfa"></param>
/// <param name="p"></param>
void ShapeCircle::Rotate(double alfa, Point2D p) {
	point.x = p.x + (point.x - p.x) * cos(alfa) - (point.y - p.y) * sin(alfa);
	point.y = p.y + (point.x - p.x) * sin(alfa) - (point.y - p.y) * cos(alfa);
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}
/// Skalowanie ko�a
/// <param name="kx">wsp�czynnik skalowania wsp�rz�dnej x</param>
/// <param name="ky">wsp�czynnik skalowania wsp�rz�dnej y</param>
/// <param name="p">?</param>
void ShapeCircle::Scaling(double kx, double ky, Point2D p) {
	point.x = point.x * kx + (1 - kx) * p.x;
	point.y = point.y * ky + (1 - ky) * p.y;
	radius = radius * ky * kx;
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}