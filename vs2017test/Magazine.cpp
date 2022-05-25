#include "Magazine.h"

Magazine::Magazine()
{
	for (int i = 0; i < NUM_BULLETS_PER_MAGAZINE; i++) {
		bullets[i] = new Bullet();
	}
}

void Magazine::fire()
{
	if (bullets_left > 0) {
		bullets[bullets_left - 1]->Fire();
		bullets[bullets_left - 1] = nullptr;
		bullets_left--;
	}
}
