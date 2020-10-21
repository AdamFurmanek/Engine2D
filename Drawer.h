#ifndef Drawer_h
#define Drawer_h

#include "Engine.h"
#include <stack>

using namespace std;

class Drawer
{
private:
	ALLEGRO_BITMAP* buffer;
public:
	Drawer(ALLEGRO_BITMAP* buffer);

	void Clear();
	void DrawPixels(vector <Point2D> pixels);
	void DrawTriangle(Point2D a, Point2D b, Point2D c, ALLEGRO_COLOR co);
	void DrawLineSegment(LineSegment lineSegment);
	void DrawLineSegment(vector <LineSegment> lineSegment);
	void DrawLineSegment(vector <Point2D> pixels, bool open);
	void DrawCircle(Point2D point, double R, bool octagonalSymetry);
	void Fill(Point2D point, bool Recursion);
	void FillSet(Point2D p, ALLEGRO_COLOR wantedColor);
	void FillRecursion(Point2D point, ALLEGRO_COLOR wantedColor);
};
#endif
