#include "SpriteObject.h"
#include "BitmapHandler.h"
#include "Enums.h"

SpriteObject::SpriteObject(double x, double y) {
	this->x = x;
	this->y = y;
}

void SpriteObject::draw(ALLEGRO_BITMAP* buffer) {
	timer++;
	if (timer >= animationSpeed) {
		timer = 0;
		if (actualFrame >= bitmaps.size()-1)
			actualFrame = 0;
		else
			actualFrame++;
	}

	al_set_target_bitmap(buffer);
	al_draw_bitmap(bitmaps[actualFrame], x, y, 0);
}

void SpriteObject::drawFlipHorizontal(ALLEGRO_BITMAP* buffer) {
	timer++;
	if (timer >= animationSpeed) {
		timer = 0;
		if (actualFrame >= bitmaps.size())
			actualFrame = 0;
		else
			actualFrame++;
	}
	al_draw_bitmap(bitmaps[actualFrame], x, y, ALLEGRO_FLIP_HORIZONTAL);
}

void SpriteObject::addBitmap(ALLEGRO_BITMAP* bitmap) {
	bitmaps.push_back(bitmap);
}

void SpriteObject::deleteBitmaps() {
	bitmaps.clear();
}

vector <ALLEGRO_BITMAP*> SpriteObject::getBitmaps() {
	return bitmaps;
}
