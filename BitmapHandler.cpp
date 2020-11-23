#include "BitmapHandler.h"
#include <iostream>
#include <allegro5\allegro_image.h>

/// struktura do przechowywania bitmapy
ALLEGRO_BITMAP* BitmapHandler::getBitmap() {
	return bitmap;
}
/// tworzy bitmape o okre�lonej wysoko�ci i szeroko�ci
void BitmapHandler::create(int width, int height) {
	if (bitmap != NULL)
		destroy();
	bitmap = al_create_bitmap(width, height);
}
/// usuwa bitmap�
void BitmapHandler::destroy() {
	al_destroy_bitmap(bitmap);
	bitmap = NULL;
}
/// �aduje zawarto�� z filepath i przypisuje j� do bitmap; metoda c_str zwraca �a�cuch znak�w tylko do odczytu
void BitmapHandler::load(string filepath) {
	if (bitmap != NULL)
		destroy();
	bitmap = al_load_bitmap(filepath.c_str());
}
/// zapisuje/nadpisuje zawarto�� bitmap do filepath
void BitmapHandler::save(string filepath) {
	al_save_bitmap(filepath.c_str(), bitmap);
}