// 1D Adventure : 1 dimension game with simple console output.

#include "stdafx.h"
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Point.h"
#include "Rain.h"
#include "MeteorologicalManager.h"
#include "GameWorld.h"

#define ESCAPE_KEY     27
#define KEY_LEFT       'a'
#define KEY_RIGHT      'd'
#define KEY_SHOT_LEFT  'q'
#define KEY_SHOT_RIGHT 'e'

bool keyboardController(int &key, GameWorld *world);

int main() {
	GameWorld world;

	// Declare keyboard key
	int key = 0;

	bool gameOver = false;

	while (keyboardController(key, &world) && !gameOver) {
		gameOver = world.runGame();
	}

	return 0;
}

bool keyboardController(int &key, GameWorld *world) {
	if (_kbhit()) {
		// Get the pressed key
		key = _getch();

		switch (key) {
			// Move pj to the left
		case KEY_LEFT:
			world->moveCharacterLeft();
			break;
			// Move pj to the right
		case KEY_RIGHT:
			world->moveCharacterRight();
			break;
			// Shot to the left
		case KEY_SHOT_LEFT:
			world->shootLeft();
			break;
			// Shot to the right
		case KEY_SHOT_RIGHT:
			world->shootRight();
			break;
		}
	}

	if (key == ESCAPE_KEY) {
		return false;
	}
	else {
		return true;
	}
}