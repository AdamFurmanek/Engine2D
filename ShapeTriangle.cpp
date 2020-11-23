#include "ShapeTriangle.h"

/// Inicjacja punkt�w ShapeTriangle
/// <param name="a">pierwszy punkt tr�jk�ta </param>
/// <param name="b">drugi punkt tr�jk�ta </param>
/// <param name="c">trzeci punkt tr�jk�ta </param>
ShapeTriangle::ShapeTriangle(Point2D a, Point2D b, Point2D c) : Shape() {
	this->a = a;
	this->b = b;
	this->c = c;
	generateBB();
}

/// Funkcja generauj�ca odpowiedni� granic� kolizji
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

/// Funkcja rysuj�ca tr�jk�t
/// <param name="buffer"> g��wny bitmapa(okienko ekranu)</param>
void ShapeTriangle::Draw(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawTriangle(a, b, c, a.c);
}

/// Funkcja pokazuj�ca granice kolizji
/// <param name="buffer">g��wna bitmapa(okienko ekranu)</param>
void ShapeTriangle::DrawBoundingBox(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawLineSegment(bb.getPoints(), false);
}

/// Funkcja zwracaj�ca granice kolizji (obiekt BoundingBox)
/// <returns>bb</returns>
BoundingBox ShapeTriangle::GetBoundingBox() {
	return bb;
}

/// Typ logiczny zwracaj�cy prawd� je�eli kolizja wyst�puje, lub fa�sz w przeciwnym wypadku
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

/// Obr�t tr�jk�ta
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

/// Skalowanie ko�a
/// <param name="kx">wsp�czynnik skalowania wsp�rz�dnej x</param>
/// <param name="ky">wsp�czynnik skalowania wsp�rz�dnej y</param>
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