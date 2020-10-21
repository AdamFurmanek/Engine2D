#include "Drawer.h"
#include "Engine.h"

using namespace std;

int main() {
		Engine* eng = Engine::GetInstance();

		eng->Init("Test Silnika 2D", false, SVGA);

		Drawer* drawer = new Drawer(eng->GetBuffer());

		drawer->Clear();

		/* Test metod DrawTriangle i DrawPixels */
		{
			Point2D point1 = { 100, 100, Red };
			Point2D point2 = { 300, 100, Red };
			Point2D point3 = { 100, 300, Red };

			vector <Point2D> pixels;
			pixels.push_back(point1);
			pixels.push_back(point2);
			pixels.push_back(point3);

			drawer->DrawTriangle(point1, point2, point3, Blue);
			drawer->DrawPixels(pixels);
		}
		/* Test metod DrawLineSegment */
		{

			vector <Point2D> pixels;
			pixels.push_back({ 200, 300, Red });
			pixels.push_back({ 400, 400, Red });
			pixels.push_back({ 500, 300, Red });
			pixels.push_back({ 400, 200, Red });

			drawer->DrawLineSegment(pixels, false);

			vector <LineSegment> lineSegments;
			LineSegment ls1 = { { 700, 200, NULL }, { 600, 100, NULL }, Green };
			LineSegment ls2 = { { 600, 100, NULL }, { 400, 100, NULL }, Green };
			LineSegment ls3 = { { 400, 100, NULL }, { 700, 200, NULL }, Green };
			lineSegments.push_back(ls1);
			lineSegments.push_back(ls2);
			lineSegments.push_back(ls3);

			drawer->DrawLineSegment(lineSegments);
		}

		/* Test Viewport */
		{
			Viewport viewport = { { 50, 50, White }, { 450, 450, White } };
			drawer->DrawLineSegment(viewport.getPoints(), false);

			vector <LineSegment> lineSegments;
			LineSegment ls1 = { { 100, 300, NULL }, { 200, 350, NULL }, DarkGreen };
			LineSegment ls2 = { { 200, 350, NULL }, { 300, 500, NULL }, DarkGreen };
			LineSegment ls3 = { { 300, 500, NULL }, { 100, 500, NULL }, DarkGreen };
			LineSegment ls4 = { { 25, 200, NULL }, { 600, 200, NULL }, DarkGreen };
			lineSegments.push_back(ls1);
			lineSegments.push_back(ls2);
			lineSegments.push_back(ls3);
			//drawer->DrawLineSegment(lineSegments);
			drawer->DrawLineSegment(viewport.cut(lineSegments));
			//drawer->DrawLineSegment(ls4);
			drawer->DrawLineSegment(viewport.cut(ls4));
		}

		/* Test DrawCircle i Fill */
		{
			drawer->DrawCircle({ 600, 300, Orange }, 70, true);

			drawer->Fill({ 120,120, DarkRed }, false);
		}
		

		eng->MainLoop();

	return 0;
}