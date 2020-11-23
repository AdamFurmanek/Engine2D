#include "ShapeTriangle.h"

/// Inicjacja punktów ShapeTriangle
/// <param name="a">pierwszy punkt trójk¹ta </param>
/// <param name="b">drugi punkt trójk¹ta </param>
/// <param name="c">trzeci punkt trójk¹ta </param>
ShapeTriangle::ShapeTriangle(Point2D a, Point2D b, Point2D c) : Shape() {
	this->a = a;
	this->b = b;
	this->c = c;
	generateBB();
}

/// Funkcja generauj¹ca odpowiedni¹ granicê kolizji
void ShapeTriangle::generateBB() {
	double maxX = a.x > b.x ? a.x : b.x;
	maxX = maxX > c.x ? maxX : c.x;

	double maxY = a.y > b.y ? a.y : b.y;
	maxY = maxY > c.y ? maxY : c.y;

	double minX = a.x < b.x ? a.x : b.x;
	minX = minX < c.x ? minX : c.x;

	double minY = a.y < b.y ? a.y : b.y;
	minY = minY < c.y ? minY : c.y;
	this->bb = { {minX, minY, a.c}, { maxX, maxY ,a.c } };
}

/// Funkcja rysuj¹ca trójk¹t
/// <param name="buffer"> g³ówny bitmapa(okienko ekranu)</param>
void ShapeTriangle::Draw(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawTriangle(a, b, c, a.c);
}

/// Funkcja pokazuj¹ca granice kolizji
/// <param name="buffer">g³ówna bitmapa(okienko ekranu)</param>
void ShapeTriangle::DrawBoundingBox(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawLineSegment(bb.getPoints(), false);
}

/// Funkcja zwracaj¹ca granice kolizji (obiekt BoundingBox)
/// <returns>bb</returns>
BoundingBox ShapeTriangle::GetBoundingBox() {
	return bb;
}

/// Typ logiczny zwracaj¹cy prawdê je¿eli kolizja wystêpuje, lub fa³sz w przeciwnym wypadku
/// <param name="bb2"></param>
/// <returns>true/false</returns>
bool ShapeTriangle::Collison(BoundingBox bb2) {
	if (bb2.Colission(bb2, bb))
		return true;
	return false;
}

/// Translacja o wektor
/// <param name="x"></param>
/// <param name="y"></param>
void ShapeTriangle::VectorTranslation(double x, double y) {
	a.x += x;
	b.x += x;
	c.x += x;

	a.y += y;
	b.y += y;
	c.y += y;

	generateBB();
}

/// Obrót trójk¹ta
/// <param name="alfa"></param>
/// <param name="p"></param>
void ShapeTriangle::Rotate(double alfa, Point2D p) {
	a.x = p.x + (a.x - p.x) * cos(alfa) - (a.y - p.y) * sin(alfa);
	a.y = p.y + (a.x - p.x) * sin(alfa) - (a.y - p.y) * cos(alfa);

	b.x = p.x + (b.x - p.x) * cos(alfa) - (b.y - p.y) * sin(alfa);
	b.y = p.y + (b.x - p.x) * sin(alfa) - (b.y - p.y) * cos(alfa);

	c.x = p.x + (c.x - p.x) * cos(alfa) - (c.y - p.y) * sin(alfa);
	c.y = p.y + (c.x - p.x) * sin(alfa) - (c.y - p.y) * cos(alfa);

	generateBB();
}

/// Skalowanie ko³a
/// <param name="kx">wspó³czynnik skalowania wspó³rzêdnej x</param>
/// <param name="ky">wspó³czynnik skalowania wspó³rzêdnej y</param>
/// <param name="p">?</param>
void ShapeTriangle::Scaling(double kx, double ky, Point2D p) {
	a.x = a.x * kx + (1 - kx) * p.x;
	a.y = a.y * ky + (1 - ky) * p.y;

	b.x = b.x * kx + (1 - kx) * p.x;
	b.y = b.y * ky + (1 - ky) * p.y;

	c.x = c.x * kx + (1 - kx) * p.x;
	c.y = c.y * ky + (1 - ky) * p.y;

	generateBB();
}