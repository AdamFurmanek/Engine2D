#ifndef SpriteObject_h
#define SpriteObject_h

#include <allegro5/allegro.h>
#include "Drawer.h"
#include "Enums.h"
#include <vector> 


using namespace std;

class SpriteObject
{
private:
	vector <ALLEGRO_BITMAP*> bitmaps;
	int animationSpeed = 7, timer = 0, actualFrame = 0;
	double x, y;
	double destinationX, destinationY;
public:
	SpriteObject(double x=0, double y=0);
	void draw(ALLEGRO_BITMAP* buffer);
	void drawFlipHorizontal(ALLEGRO_BITMAP* buffer);
	void addBitmap(ALLEGRO_BITMAP* bitmap);
	void deleteBitmaps();
	vector <ALLEGRO_BITMAP*> getBitmaps();
	void move(direction dr, int pixels);
	void Destination(int pixels);
	void moveDestination(double x, double y);
};


#endif