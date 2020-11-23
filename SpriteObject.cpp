#include "SpriteObject.h"
#include "BitmapHandler.h"
#include "Enums.h"
/// Konstruktor przyjmuj¹cy wspó³rzêdne
/// <param name="x"></param>
/// <param name="y"></param>
SpriteObject::SpriteObject(double x, double y) {
	this->x = x;
	this->y = y;
	destinationX = x;
	destinationY = y;
}
/// Funkcja rysuj¹ca obiekt (animuj¹ca go)
/// <param name="buffer">g³ówna bitmapa(okienko ekranu)</param>
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
/// Funkcja rysuj¹ca obiekt (animuj¹ca go) odwróconego horyzontalnie
/// <param name="buffer">g³ówna bitmapa(okienko ekranu)</param>
void SpriteObject::drawFlipHorizontal(ALLEGRO_BITMAP* buffer) {
	timer++;
	if (timer >= animationSpeed) {
		timer = 0;
		if (actualFrame >= bitmaps.size())
			actualFrame = 0;
		else
			actualFrame++;
	}
	al_set_target_bitmap(buffer);
	al_draw_bitmap(bitmaps[actualFrame], x, y, ALLEGRO_FLIP_HORIZONTAL);
}
/// Dodanie sprite'a (klatki animacji)
/// <param name="bitmap"></param>
void SpriteObject::addBitmap(ALLEGRO_BITMAP* bitmap) {
	bitmaps.push_back(bitmap);
}
/// Usuniêcie wszystkich sprite'ów (klatek animacji)
void SpriteObject::deleteBitmaps() {
	bitmaps.clear();
}
/// Zwrócenie wszystkich sprite'ów
/// <returns>bitmaps</returns>
vector <ALLEGRO_BITMAP*> SpriteObject::getBitmaps() {
	return bitmaps;
}

/// Przesuniêcie w podanym kierunku o podan¹ odleg³oœæ w pikselach
void SpriteObject::move(direction dr, int pixels) {

	switch (dr) {
	case UP:
		y -= pixels;
		break;
	case RIGHT:
		x += pixels;
		break;
	case DOWN:
		y += pixels;
		break;
	case LEFT:
	default:
		x -= pixels;
		break;
	}
	destinationX = x;
	destinationY = y;
}

/// Przesuniêcie w kierunku wyznaczonej wczeœniej lokalizacji o podan¹ odleg³oœæ w pikselach
void SpriteObject::Destination(int pixels) {
	if (destinationX > x + pixels)
		x += pixels;
	if (destinationX < x - pixels)
		x -= pixels;
	if (destinationY > y + pixels)
		y += pixels;
	if (destinationY < y - pixels)
		y -= pixels;
}

/// Wyznaczenie nastêpnej lokalizacji
void SpriteObject::moveDestination(double x, double y) {
	destinationX = x;
	destinationY = y;
}