#include "ShapeObjectCircle.h"

using namespace std;

ShapeObjectCircle::ShapeObjectCircle(ShapeCircle sc) : ShapeObject() {
	this->sc = sc;
}

void ShapeObjectCircle::SetShapeCircle(ShapeCircle sc) {
	this->sc = sc;
}

ShapeCircle ShapeObjectCircle::getShapCircle() {
	return sc;
}

void ShapeObjectCircle::Draw(ALLEGRO_BITMAP* buffer) {
	sc.Draw(buffer);
}

BoundingBox ShapeObjectCircle::GetBoundingBox() {
	return sc.GetBoundingBox();
}

bool ShapeObjectCircle::Collison(BoundingBox bb2) {
	return sc.Collison(bb2);
}

void ShapeObjectCircle::VectorTranslation(double x, double y) {
	sc.VectorTranslation(x, y);
}

void ShapeObjectCircle::Rotate(double alfa, Point2D p) {
	sc.Rotate(alfa, p);
}

void ShapeObjectCircle::Scaling(double kx, double ky, Point2D p) {
	sc.Scaling(kx, ky, p);
}