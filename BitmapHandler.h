#ifndef BitmapHandler_h
#define BitmapHandler_h


#include <allegro5/allegro.h>
#include <iostream>

using namespace std;

class BitmapHandler
{
private:
	ALLEGRO_BITMAP* bitmap = NULL;
public:
	ALLEGRO_BITMAP* getBitmap();
	void create(int width, int height);
	void destroy();
	void load(string filepath);
	void save(string filepath);
};

#endif