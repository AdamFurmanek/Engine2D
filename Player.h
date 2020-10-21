#ifndef Player_h
#define Player_h

#include "Enums.h"

class Player
{
private:
	double x, y;
public:
	void move(direction dr, int pixels);
};

#endif