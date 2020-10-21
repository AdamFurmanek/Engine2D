#ifndef Shape_h
#define Shape_h

#include "Point2D.h"
#include "BoundingBox.h"
#include "Drawer.h"

using namespace std;

class Shape
{
protected:
	BoundingBox bb;
public:
	Shape() {}
	void Draw(ALLEGRO_BITMAP* buffer);
	void DrawBoundingBox(ALLEGRO_BITMAP* buffer);
	BoundingBox GetBoundingBox();
	bool Collison(BoundingBox bb2);
	void VectorTranslation(double x, double y);
	void Rotate(double alfa, Point2D p);
	void Scaling(double kx, double ky, Point2D p);
};

#endif