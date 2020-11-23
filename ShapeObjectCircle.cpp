#include "ShapeObjectCircle.h"

using namespace std;
/// Konstruktor przymuj¹cy obiekt typu ShapeCircle
/// <param name="sc"></param>
ShapeObjectCircle::ShapeObjectCircle(ShapeCircle sc) : ShapeObject() {
	this->sc = sc;
}
/// Funkcja ustawiaj¹ca obiekt typu ShapeCircle
/// <param name="sc"></param>
void ShapeObjectCircle::SetShapeCircle(ShapeCircle sc) {
	this->sc = sc;
}
/// Funkcja zwracaj¹ca obiekt typu ShapeCircle
/// <returns>sc</returns>
ShapeCircle ShapeObjectCircle::getShapCircle() {
	return sc;
}
/// Rysowanie na podanym bufferze
/// <param name="buffer">g³ówny obiekt bitmapy(okienko ekranu)</param>
void ShapeObjectCircle::Draw(ALLEGRO_BITMAP* buffer) {
	sc.Draw(buffer);
}
/// Funkcja zwracaj¹ca granice kolizji
/// <returns>sc</returns>
BoundingBox ShapeObjectCircle::GetBoundingBox() {
	return sc.GetBoundingBox();
}
/// Funkcja sprawdzaj¹ca kolizjê z innym obiektem BoundingBox
/// <param name="bb2"></param>
/// <returns>sc</returns>
bool ShapeObjectCircle::Collison(BoundingBox bb2) {
	return sc.Collison(bb2);
}
/// Translacja o wektor
/// <param name="x"></param>
/// <param name="y"></param>
void ShapeObjectCircle::VectorTranslation(double x, double y) {
	sc.VectorTranslation(x, y);
}
/// Obrót ko³a
/// <param name="alfa"></param>
/// <param name="p"></param>
void ShapeObjectCircle::Rotate(double alfa, Point2D p) {
	sc.Rotate(alfa, p);
}
/// Skalowanie ko³a
/// <param name="kx"></param>
/// <param name="ky"></param>
/// <param name="p"></param>
void ShapeObjectCircle::Scaling(double kx, double ky, Point2D p) {
	sc.Scaling(kx, ky, p);
}