#include <iostream>
#include "Engine.h"
#include <vector>

using namespace std;

int main() {
		Engine* eng = Engine::GetInstance();

		eng->Init("Test Silnika 2D", false, SVGA);

		eng->Clear();

		/* Test metody DrawTriangle i DrawPixels */
		Point2D point1 = { 200, 200, al_map_rgb(255, 0, 0) };
		Point2D point2 = { 500, 500, al_map_rgb(255, 0, 0) };
		Point2D point3 = { 500, 200, al_map_rgb(255, 0, 0) };

		vector <Point2D> pixels;
		pixels.push_back(point1);
		pixels.push_back(point2);
		pixels.push_back(point3);

		eng->DrawTriangle(point1, point2, point3, al_map_rgb(0, 0, 255));
		eng->DrawPixels(pixels);

		eng->MainLoop();

	return 0;
}