#include "Drawer.h"

using namespace std;

Drawer::Drawer(ALLEGRO_BITMAP* buffer) {
	this->buffer = buffer;
}

void Drawer::Clear() {
	al_set_target_bitmap(buffer);
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Drawer::DrawPixels(vector <Point2D> pixels) {
	al_set_target_bitmap(buffer);
	for (int i = 0; i < pixels.size();i++) {
		al_draw_pixel(pixels[i].x, pixels[i].y, pixels[i].c);
	}
}

void Drawer::DrawTriangle(Point2D a, Point2D b, Point2D c, ALLEGRO_COLOR co) {
	al_set_target_bitmap(buffer);
	al_draw_triangle(a.x, a.y, b.x, b.y, c.x, c.y, co, 1);
}

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

void Drawer::DrawLineSegment(vector <LineSegment> lineSegment) {
	al_set_target_bitmap(buffer);
	for (int i = 0; i < lineSegment.size();i++) {
		DrawLineSegment(lineSegment[i]);
	}
}

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
