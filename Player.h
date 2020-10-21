#ifndef Player_h
#define Player_h

#include "Enums.h"

class Player
{
private:
	double x, y;
public:
	void move(direction dr, int pixels) {

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
	}
};

#endif