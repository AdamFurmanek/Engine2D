#pragma once
#ifndef ShapeObject_h
#define ShapeObject_h

#include "Point2D.h"
#include "BoundingBox.h"
#include "Drawer.h"

using namespace std;

class ShapeObject
{
public:
	ShapeObject() {}
	void Draw(ALLEGRO_BITMAP* buffer);
	BoundingBox GetBoundingBox();
	bool Collison(BoundingBox bb2);
	void VectorTranslation(double x, double y);
	void Rotate(double alfa, Point2D p);
	void Scaling(double kx, double ky, Point2D p);
};

#endif