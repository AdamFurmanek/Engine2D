#include "Drawer.h"

using namespace std;
/// Utworzenie ekranu dla Drawer'a (przeró¿nych funkcji rysuj¹cych punkty, odcinki, figury) o nazwie buffer, na której bêd¹ wykonywane kolejne czynnoœci
/// <param name="buffer">g³ówny obiekt bitmapy(okienko ekranu)</param>
Drawer::Drawer(ALLEGRO_BITMAP* buffer) {
	this->buffer = buffer;
}
/// Wyczyszczenie buffer'a
void Drawer::Clear() {
	al_set_target_bitmap(buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}
/// Funkcja rysuj¹ca punkt - DrawPixels
/// <param name="pixels">wektor dwuwymiarowy - kontener dla punktów </param>
void Drawer::DrawPixels(vector <Point2D> pixels) {
	al_set_target_bitmap(buffer);
	for (int i = 0; i < pixels.size();i++) {
		al_draw_pixel(pixels[i].x, pixels[i].y, pixels[i].c);
	}
}
/// Funkcja rysuj¹ca trójk¹t - DrawTriangle
/// <param name="a">pierwsza wspó³rzêdna x,y </param>
/// <param name="b">druga wspó³rzêdna x,y</param>
/// <param name="c">trzecia wspó³rzêdna x,y</param>
/// <param name="co">zmienna przechowuj¹ca kolor</param>
void Drawer::DrawTriangle(Point2D a, Point2D b, Point2D c, ALLEGRO_COLOR co) {
	al_set_target_bitmap(buffer);
	al_draw_triangle(a.x, a.y, b.x, b.y, c.x, c.y, co, 1);
}
/// Funkcja rysuj¹ca punkt lub odcinek - DrawLineSegment 
/// <param name="lineSegment">kontener wspó³rzêdnych dla klasy LineSegment</param>
void Drawer::DrawLineSegment(LineSegment lineSegment) {
	al_set_target_bitmap(buffer);
	double x0, x1, y0, y1;
	if (lineSegment.getA().x < lineSegment.getB().x) {
		x0 = lineSegment.getA().x;
		x1 = lineSegment.getB().x;
		y0 = lineSegment.getA().y;
		y1 = lineSegment.getB().y;
	}
	else {
		x0 = lineSegment.getB().x;
		x1 = lineSegment.getA().x;
		y0 = lineSegment.getB().y;
		y1 = lineSegment.getA().y;
	}

	double dx = x1 - x0;
	double dy = y1 - y0;

	/* Punkt */
	if (dx == 0 && dy == 0) {
		al_draw_pixel(x0, int(y0), lineSegment.getC());
		return;
	}
	/* Pionowy odcinek */
	else if (dx == 0) {
		if (y0 > y1) {
			double temporary = y0;
			y0 = y1;
			y1 = temporary;
		}
		for (int y = y0;y <= y1;y++) {
			al_draw_pixel(x0, y, lineSegment.getC());
		}
	}
	/* Poziomy odcinek */
	else if (dy == 0) {
		for (int x = x0;x <= x1;x++) {
			al_draw_pixel(x, y0, lineSegment.getC());
		}
	}
	/* Skoœny odcinek */
	else {
		double m = dy / dx;
		double y = y0;
		for (int x = x0;x <= x1;x++) {
			al_draw_pixel(x, int(y + 0.5), lineSegment.getC());
			y += m;
		}
	}
}
/// Przeci¹¿enie funkcji lineSegment, przyjmuj¹ce ca³e tablice odcinków
/// <param name="lineSegment">kontener wspó³rzêdnych dla klasy LineSegment</param>
void Drawer::DrawLineSegment(vector <LineSegment> lineSegment) {
	al_set_target_bitmap(buffer);
	for (int i = 0; i < lineSegment.size();i++) {
		DrawLineSegment(lineSegment[i]);
	}
}
/// Przeci¹¿enie funkcji lineSegment, przyjmuj¹ce ca³e tablice pikseli
/// <param name="pixels"> wektor dwuwymiarowy - kontener dla punktów</param>
/// <param name="open"> typ logiczny decyduj¹cy czy figura ma po³¹czyæ pierwszy i ostatni punkt </param>
void Drawer::DrawLineSegment(vector <Point2D> pixels, bool open) {
	al_set_target_bitmap(buffer);
	for (int i = 0; i < pixels.size()-1;i++) {
		LineSegment ls = { pixels[i], pixels[i + 1], pixels[i].c };
		DrawLineSegment(ls);
	}
	if (!open) {
		LineSegment ls = { pixels[0], pixels[pixels.size()-1], pixels[0].c };
		DrawLineSegment(ls);
	}
}
/// Funkcja rysuj¹ca ko³o - DrawCircle 
/// <param name="point"> punkt dwuwymiarowy okreœlaj¹cy œrodek ko³a</param>
/// <param name="R">promieñ ko³a</param>
/// <param name="octagonalSymetry">typ logiczny - ...? </param>
void Drawer::DrawCircle(Point2D point, double R, bool octagonalSymetry) {
	al_set_target_bitmap(buffer);
	double PI = 3.14159265358979323846;
	double x0 = point.x;
	double y0 = point.y;
	if (!octagonalSymetry) {
		for (double a = 0;a < PI / 2;a += (1 / R)) {
			al_put_pixel(x0 + R * cos(a), y0 + R * sin(a), point.c);
			al_put_pixel(x0 - R * cos(a), y0 + R * sin(a), point.c);
			al_put_pixel(x0 + R * cos(a), y0 - R * sin(a), point.c);
			al_put_pixel(x0 - R * cos(a), y0 - R * sin(a), point.c);
		}
	}
	else {
		for (double a = 0;a < PI / 4;a += (1 / R)) {
			al_put_pixel(x0 + R * cos(a), y0 + R * sin(a), point.c);
			al_put_pixel(x0 - R * cos(a), y0 + R * sin(a), point.c);
			al_put_pixel(x0 + R * cos(a), y0 - R * sin(a), point.c);
			al_put_pixel(x0 - R * cos(a), y0 - R * sin(a), point.c);

			al_put_pixel(x0 + R * sin(a), y0 + R * cos(a), point.c);
			al_put_pixel(x0 - R * sin(a), y0 + R * cos(a), point.c);
			al_put_pixel(x0 + R * sin(a), y0 - R * cos(a), point.c);
			al_put_pixel(x0 - R * sin(a), y0 - R * cos(a), point.c);
		}
	}
}
/// Funkcja wywo³uj¹ca metodê wype³nienia obszaru ekranu, w którym dany punkt siê znajduje
/// <param name="point"> punkt dwuwymiarowy o dowolnych wspó³rzêdnych</param>
/// <param name="Recursion"> typ logiczny - je¿eli prawdziwy to wywo³a FillRecursion, jeœli nie to FillSet</param>
void Drawer::Fill(Point2D point, bool Recursion) {
	if (Recursion)
		FillRecursion(point, al_get_pixel(buffer, point.x, point.y));
	else
		FillSet(point, al_get_pixel(buffer, point.x, point.y));
}
/// Funkcja wykorzystuj¹ca stos do wype³nienia obszaru ekranu, w którym dany punkt siê znajduje
/// <param name="p"> punkt dwuwymiarowy dla dowolnych wspó³rzêdnych</param>
/// <param name="wantedColor"> porz¹dany kolor</param>
void Drawer::FillSet(Point2D p, ALLEGRO_COLOR wantedColor) {
	stack<Point2D> stack;

	stack.push(p);

	while (stack.size() > 0) {
		Point2D point = stack.top();
		stack.pop();

		if (!memcmp(&al_get_pixel(buffer, point.x, point.y), &wantedColor, sizeof(ALLEGRO_COLOR))) {
			al_put_pixel(point.x, point.y, p.c);

			stack.push({ point.x - 1, point.y });
			stack.push({ point.x + 1, point.y });
			stack.push({ point.x, point.y - 1 });
			stack.push({ point.x, point.y + 1 });
		}
	}
}
/// Funkcja wykorzystuj¹ca rekurencjê do wype³nienia obszaru ekranu, w którym dany punkt siê znajduje
/// <param name="point"> punkt dwuwymiarowy dla dowolnych wspó³rzêdnych</param>
/// <param name="wantedColor"> porz¹dany kolor</param>
void Drawer::FillRecursion(Point2D point, ALLEGRO_COLOR wantedColor) {
	if (!memcmp(&al_get_pixel(buffer, point.x, point.y), &wantedColor, sizeof(ALLEGRO_COLOR))) {
		al_put_pixel(point.x, point.y, point.c);
		FillRecursion({ point.x, point.y - 1, point.c }, wantedColor);
		FillRecursion({ point.x - 1, point.y, point.c }, wantedColor);
		FillRecursion({ point.x, point.y + 1, point.c }, wantedColor);
		FillRecursion({ point.x + 1, point.y, point.c }, wantedColor);
	}
}