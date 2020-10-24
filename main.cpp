#include <allegro5/allegro.h>
#include "Point2D.h"
#include "Enums.h"
#include "BoundingBox.h"
#include <iostream>
#include "Drawer.h"
#include "Viewport.h"
#include "ShapeCircle.h"
#include "ShapeObjectCircle.h"
#include "Engine.h"
#include "BitmapHandler.h"

using namespace std;

int main() {
		Engine* eng = Engine::GetInstance();

		eng->Init("Test Silnika 2D", false, HD);

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

		/* Test BoundingBox */
		{
			BoundingBox bb1 = { { 800, 400, Red } ,{ 900, 300, Red } };
			BoundingBox bb2 = { { 750, 350, Blue } ,{ 850, 450, Blue } };
			BoundingBox bb3 = { { 1000, 350, Yellow } ,{ 1100, 450, Yellow } };
			drawer->DrawLineSegment(bb1.getPoints(), false);
			drawer->DrawLineSegment(bb2.getPoints(), false);
			drawer->DrawLineSegment(bb3.getPoints(), false);

			if (bb1.Colission(bb1, bb2))
				cout << "Kolizja BoundingBox1 i BoundingBox2\n";
			if (bb1.Colission(bb1, bb3))
				cout << "Kolizja BoundingBox1 i BoundingBox3\n";
		}

		/* Test Shape i ShapeObject */
		{
			ShapeCircle shapeCircle = { { 800, 600, Red } , 50 };
			shapeCircle.Draw(eng->GetBuffer());
			shapeCircle.DrawBoundingBox(eng->GetBuffer());

			ShapeCircle shapeCircle2 = { { 850, 650, Blue } , 50 };
			shapeCircle2.Draw(eng->GetBuffer());
			shapeCircle2.DrawBoundingBox(eng->GetBuffer());
			if (shapeCircle.Collison(shapeCircle2.GetBoundingBox()))
				cout << "Kolizja ShapeCircle1 i ShapeCircle2\n";
			shapeCircle2.VectorTranslation(-400, 0);
			shapeCircle2.Draw(eng->GetBuffer());
			shapeCircle2.DrawBoundingBox(eng->GetBuffer());

			shapeCircle.Rotate(0.5, { 750,600 });
			shapeCircle.Draw(eng->GetBuffer());
			shapeCircle.DrawBoundingBox(eng->GetBuffer());

			shapeCircle.Scaling(2, 1, { 750,600 });
			shapeCircle.Draw(eng->GetBuffer());
			shapeCircle.DrawBoundingBox(eng->GetBuffer());


			ShapeObjectCircle soc = { shapeCircle2 };
			soc.VectorTranslation(400, -400);
			soc.Draw(eng->GetBuffer());
			soc.SetShapeCircle({ { 0, 0, Red } , 50 });
			soc.Draw(eng->GetBuffer());
		}
		/* Test BitmapHandler */
		{
			BitmapHandler bh;
			bh.create(20, 20);
			al_set_target_bitmap(bh.getBitmap());
			al_clear_to_color(Red);
			bh.save("Bitmaps\\bitmap1.bmp");

			bh.load("Bitmaps\\bitmap1.bmp");
			al_set_target_bitmap(eng->GetBuffer());
			al_draw_bitmap(bh.getBitmap(), 0, 0, 0);
		}
		/* Test SpriteObject */
		BitmapHandler bh1, bh2, bh3;
		bh1.create(20, 20);
		bh2.create(20, 20);
		bh3.create(20, 20);
		al_set_target_bitmap(bh1.getBitmap());
		al_clear_to_color(Red);
		al_set_target_bitmap(bh2.getBitmap());
		al_clear_to_color(Green);
		al_set_target_bitmap(bh3.getBitmap());
		al_clear_to_color(Blue);
		SpriteObject so;
		so.addBitmap(bh1.getBitmap());
		so.addBitmap(bh2.getBitmap());
		so.addBitmap(bh3.getBitmap());
		eng->spriteObject = &so;
		eng->spriteObject->draw(eng->GetBuffer());

		eng->MainLoop();

	return 0;
}

void Test() {

}