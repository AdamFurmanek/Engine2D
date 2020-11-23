#ifndef ShapeTriangle_h
#define ShapeTriangle_h

#include "Shape.h"
#include "Point2D.h"
#include "BoundingBox.h"
#include "Drawer.h"

using namespace std;

class ShapeTriangle : public Shape
{
private:
	Point2D a, b, c;
	void generateBB();
public:
	ShapeTriangle(Point2D a = { 0,0,Black }, Point2D b = { 0,0,Black }, Point2D c = { 0,0,Black });
	void Draw(ALLEGRO_BITMAP* buffer);
	void DrawBoundingBox(ALLEGRO_BITMAP* buffer);
	BoundingBox GetBoundingBox();
	bool Collison(BoundingBox bb2);
	void VectorTranslation(double x, double y);
	void Rotate(double alfa, Point2D p);
	void Scaling(double kx, double ky, Point2D p);
};

#endif