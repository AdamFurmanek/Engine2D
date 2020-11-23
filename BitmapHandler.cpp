#include "BitmapHandler.h"
#include <iostream>
#include <allegro5\allegro_image.h>

/// struktura do przechowywania bitmapy
ALLEGRO_BITMAP* BitmapHandler::getBitmap() {
	return bitmap;
}
/// tworzy bitmape o okreœlonej wysokoœci i szerokoœci
void BitmapHandler::create(int width, int height) {
	if (bitmap != NULL)
		destroy();
	bitmap = al_create_bitmap(width, height);
}
/// usuwa bitmapê
void BitmapHandler::destroy() {
	al_destroy_bitmap(bitmap);
	bitmap = NULL;
}
/// ³aduje zawartoœæ z filepath i przypisuje j¹ do bitmap; metoda c_str zwraca ³añcuch znaków tylko do odczytu
void BitmapHandler::load(string filepath) {
	if (bitmap != NULL)
		destroy();
	bitmap = al_load_bitmap(filepath.c_str());
}
/// zapisuje/nadpisuje zawartoœæ bitmap do filepath
void BitmapHandler::save(string filepath) {
	al_save_bitmap(filepath.c_str(), bitmap);
}