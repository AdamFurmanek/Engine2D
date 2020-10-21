#ifndef ShapeCircle_h
#define ShapeCircle_h

#include "Shape.h"
#include "Point2D.h"
#include "BoundingBox.h"
#include "Drawer.h"

using namespace std;
class ShapeCircle: public Shape
{
private:
	Point2D point;
	double radius;

public:
	ShapeCircle(Point2D point = { 0,0,Black }, double radius = 0);
	void Draw(ALLEGRO_BITMAP* buffer);
	void DrawBoundingBox(ALLEGRO_BITMAP* buffer);
	BoundingBox GetBoundingBox();
	bool Collison(BoundingBox bb2);
	void VectorTranslation(double x, double y);
	void Rotate(double alfa, Point2D p);
	void Scaling(double kx, double ky, Point2D p);
};

#endif