#pragma once
#ifndef ShapeObjectCircle_h
#define ShapeObjectCircle_h

#include "Point2D.h"
#include "BoundingBox.h"
#include "Drawer.h"
#include "ShapeObject.h"
#include "ShapeCircle.h"

using namespace std;

class ShapeObjectCircle : public ShapeObject
{
protected:
	ShapeCircle sc;
public:
	ShapeObjectCircle(ShapeCircle sc);
	void SetShapeCircle(ShapeCircle sc);
	ShapeCircle getShapCircle();
	void Draw(ALLEGRO_BITMAP* buffer);
	BoundingBox GetBoundingBox();
	bool Collison(BoundingBox bb2);
	void VectorTranslation(double x, double y);
	void Rotate(double alfa, Point2D p);
	void Scaling(double kx, double ky, Point2D p);
};

#endif