#include "ShapeCircle.h"

ShapeCircle::ShapeCircle(Point2D point, double radius) : Shape() {
	this->point = point;
	this->radius = radius;
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}

void ShapeCircle::Draw(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawCircle(point, radius, true);
}

void ShapeCircle::DrawBoundingBox(ALLEGRO_BITMAP* buffer) {
	Drawer* drawer = new Drawer(buffer);
	drawer->DrawLineSegment(bb.getPoints(), false);
}

BoundingBox ShapeCircle::GetBoundingBox() {

	return bb;
}

bool ShapeCircle::Collison(BoundingBox bb2) {
	if(bb2.Colission(bb2,bb))
		return true;
	return false;
}

void ShapeCircle::VectorTranslation(double x, double y) {
	point.x += x;
	point.y += y;
	bb.setA({ bb.getA().x + x,bb.getA().y + y,bb.getA().c });
	bb.setC({ bb.getC().x + x,bb.getC().y + y,bb.getC().c });
}

void ShapeCircle::Rotate(double alfa, Point2D p) {
	point.x = p.x + (point.x - p.x) * cos(alfa) - (point.y - p.y) * sin(alfa);
	point.y = p.y + (point.x - p.x) * sin(alfa) - (point.y - p.y) * cos(alfa);
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}

void ShapeCircle::Scaling(double kx, double ky, Point2D p) {
	point.x = point.x * kx + (1 - kx) * p.x;
	point.y = point.y * ky + (1 - ky) * p.y;
	radius = radius * ky * kx;
	this->bb = { {point.x - radius, point.y - radius, point.c}, { point.x + radius, point.y + radius,point.c } };
}