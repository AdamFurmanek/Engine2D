#include "BitmapHandler.h"
#include <iostream>
#include <allegro5\allegro_image.h>

ALLEGRO_BITMAP* BitmapHandler::getBitmap() {
	return bitmap;
}

void BitmapHandler::create(int width, int height) {
	bitmap = al_create_bitmap(width, height);
}

void BitmapHandler::destroy() {
	al_destroy_bitmap(bitmap);
}

void BitmapHandler::load(string filepath) {
	bitmap = al_load_bitmap(filepath.c_str());
}

void BitmapHandler::save(string filepath) {
	al_save_bitmap(filepath.c_str(), bitmap);
}