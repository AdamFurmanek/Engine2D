#include "Player.h"

void Player::move(direction dr, int pixels) {

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