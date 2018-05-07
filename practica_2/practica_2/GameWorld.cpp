#include "stdafx.h"
#include <time.h>
#include "PaintFunctions.h"
#include "Character.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Point.h"
#include "Rain.h"
#include "MeteorologicalManager.h"
#include "GameWorld.h"

#define MAX_BULLETS 10
#define MAX_ENEMYS  6
#define MAX_POINTS  4

#define TIME_TO_ENEMY_RESPAWN 20
#define TIME_TO_POINT_RESPAWN 50

#define MAP_SIZE 80

GameWorld::GameWorld() {
	mCharacter.setPos(40);

	MeteorologicalManager mMeteorologicalManager;

	mBulletList = std::list<CBullet>(MAX_BULLETS);

	mEnemyList = std::list<CEnemy>(MAX_ENEMYS);

	mPointList = std::list<CPoint>(MAX_POINTS);

	mScore = 0;

	mEnemyRespawnTime = TIME_TO_ENEMY_RESPAWN;
	mPointRespawnTime = TIME_TO_POINT_RESPAWN;
}

CCharacter            GameWorld::getCharacter            () { return mCharacter;             }
MeteorologicalManager GameWorld::getMeteorologicalManager() { return mMeteorologicalManager; }
std::list<CBullet>    GameWorld::getBulletsList          () { return mBulletList;            }
std::list<CEnemy>     GameWorld::getEnemysList           () { return mEnemyList;             }
std::list<CPoint>     GameWorld::getPointsList           () { return mPointList;             }
int                   GameWorld::getEnemyRespawnTime     () { return mEnemyRespawnTime;      }
int                   GameWorld::getPointRespawnTime     () { return mPointRespawnTime;      }

void GameWorld::setCharacter             (CCharacter character)                        { mCharacter = character;                         }
void GameWorld::setMeteorologicalManager (MeteorologicalManager meteorologicalManager) { mMeteorologicalManager = meteorologicalManager; }
void GameWorld::setBulletsList           (std::list<CBullet> bulletsList)              { mBulletList = bulletsList;                      }
void GameWorld::setEnemysList            (std::list<CEnemy> enemysList)                { mEnemyList = enemysList;                        }
void GameWorld::setPointsList            (std::list<CPoint> pointsList)                { mPointList = pointsList;                        }
void GameWorld::setEnemyRespawnTime      (int enemyRespawnTime)                        { mEnemyRespawnTime = enemyRespawnTime;           }
void GameWorld::setPointRespawnTime      (int enemyRespawnTime)                        { mPointRespawnTime = enemyRespawnTime;           }

void GameWorld::moveCharacterLeft() {
	if (mCharacter.getPos() > 0) {
		mCharacter.setPos(mCharacter.getPos() - 1);
	}
}

void GameWorld::moveCharacterRight() {
	if (mCharacter.getPos() < MAP_SIZE) {
		mCharacter.setPos(mCharacter.getPos() + 1);
	}
}


void GameWorld::shootLeft() {
	if (mBulletList.size() < MAX_BULLETS) {
		CBullet newBullet(mCharacter.getPos() - 1, 0);
		mBulletList.push_back(newBullet);
	}
}

void GameWorld::shootRight() {
	if (mBulletList.size() < MAX_BULLETS) {
		CBullet newBullet(mCharacter.getPos() + 1, 1);
		mBulletList.push_back(newBullet);
	}
}

bool GameWorld::runGame() {
	generateElements();
	bool gameOver = checkCollisions();
	
	cleanSky();

	if (!gameOver) {
		paintProcess();

		moveElements();

		mMeteorologicalManager.updateRain();
	}
	Sleep(80);

	return gameOver;
}

void GameWorld::generateElements() {
	mMeteorologicalManager.generateRain();

	const int enemyListSize = static_cast<int>(mEnemyList.size());
	// Generate a new enemy
	if ((enemyListSize < MAX_ENEMYS) && (mEnemyRespawnTime <= 0)) {
		generateEnemy();

		mEnemyRespawnTime = TIME_TO_ENEMY_RESPAWN;
	}

	const int pointListSize = static_cast<int>(mPointList.size());
	// Generate a new point
	if ((pointListSize < MAX_POINTS) && (mPointRespawnTime <= 0)) {
		generatePoint();

		mPointRespawnTime = TIME_TO_POINT_RESPAWN;
	}
}

void GameWorld::paintProcess() {
	mMeteorologicalManager.paintRainInSky();

	gotoxy(0, 3);

	// Paint the 'map'
	for (int i = 0; i < MAP_SIZE; i++) {
		bool painted = false;

		if ((i == mCharacter.getPos()) && !painted) {
			printf("Y");
			painted = true;
		}

		if (!painted) {
			for (auto iterator = mBulletList.begin(); iterator != mBulletList.end(); iterator++) {
				if (iterator->getPos() == i) {
					if (iterator->getDir() == 0) {
						printf("<");
					}
					else {
						printf(">");
					}
					painted = true;

					break;
				}
			}
		}

		if (!painted) {
			for (auto iterator = mEnemyList.begin(); iterator != mEnemyList.end(); iterator++) {
				if (iterator->getPos() == i) {
					printf("@");
					painted = true;

					break;
				}
			}
		}

		if (!painted) {
			for (auto iterator = mPointList.begin(); iterator != mPointList.end(); iterator++) {
				if (iterator->getPos() == i) {
					printf("$");
					painted = true;

					break;
				}
			}
		}

		if (!painted) {
			bool wallDrop = mMeteorologicalManager.paintRainInWall(i);

			if (wallDrop) {
				painted = true;
			}
		}

		if (!painted) {
			printf("_");
		}
	}

	printf(" LIVES -> %d ", mCharacter.getLives());
	printf(" POINTS -> %d", mScore);
}

bool GameWorld::checkCollisions() {
	auto it = mEnemyList.begin();
	for (int j = 0; j < MAX_ENEMYS && it != mEnemyList.end(); j++) {
		if ((it->getPos() - mCharacter.getPos() == 0) || (it->getPos() - mCharacter.getPos() == 1) || (it->getPos() - mCharacter.getPos() == -1)) {
			if (mCharacter.getLives() == 1) {
				return true;
			}
			else {
				it = mEnemyList.erase(it);
				mCharacter.setLives(mCharacter.getLives() - 1);
			}
		}
	}

	auto it2 = mPointList.begin();
	for (int j = 0; j < MAX_POINTS && it2 != mPointList.end(); j++) {
		if ((it2->getPos() - mCharacter.getPos() == 0) || (it2->getPos() - mCharacter.getPos() == 1) || (it2->getPos() - mCharacter.getPos() == -1)) {
			mScore += 10;
			it2 = mPointList.erase(it2);
		}
	}

	// Checks if a bullet kills the enemy
	checkBulletWithEnemyCollision();
	// Checks if a bullet kills the point
	checkBulletWithPointCollision();

	// Erase elements out of limits
	eraseBulletsOutOfLimits ();
	eraseEnemysOutOfLimits  ();
	erasePointsOutOfLimits  ();
}

void GameWorld::moveElements () {
	// Move bullets to correct path
	for (auto iterator = mBulletList.begin(); iterator != mBulletList.end(); iterator++) {
		if (iterator->getDir() == 0) {
			iterator->setPos(iterator->getPos() - 1);
		}
		else {
			iterator->setPos(iterator->getPos() + 1);
		}
	}

	// Move point to correct path
	for (auto iterator = mPointList.begin(); iterator != mPointList.end(); iterator++) {
		if (iterator->getDir() == 0) {
			iterator->setPos(iterator->getPos() + 1);
		}
		else {
			iterator->setPos(iterator->getPos() - 1);
		}
	}

	// Move enemy to correct path
	for (auto iterator = mEnemyList.begin(); iterator != mEnemyList.end(); iterator++) {
		if (iterator->getDir() == 0) {
			iterator->setPos(iterator->getPos() + 1);
		}
		else {
			iterator->setPos(iterator->getPos() - 1);
		}
	}

	mMeteorologicalManager.updateRain();

	// Decrease counters to points and enemys respawn
	mEnemyRespawnTime--;
	mPointRespawnTime--;
}

// This function generates an enemy in enemy list
void GameWorld::generateEnemy() {
	int enemyPath = rand() % 2;
	int enemyPos = -1;
	int enemyDir = 0;

	if (enemyPath == 0) {
		enemyPos = 0;
		enemyDir = 0;
	}
	else {
		enemyPos = 80;
		enemyDir = 1;
	}

	CEnemy newEnemy(enemyPos, enemyDir);

	mEnemyList.push_back(newEnemy);
}

// This function generates an point in point list
void GameWorld::generatePoint() {
	int pointPath = rand() % 2;
	int pointPos = -1;
	int pointDir = 0;

	if (pointPath == 0) {
		pointPos = 0;
		pointDir = 0;
	}
	else {
		pointPos = 80;
		pointDir = 1;
	}

	CPoint newPoint(pointPos, pointDir);

	mPointList.push_back(newPoint);
}

// This function checks if any bullet kills any enemy and erase both
void GameWorld::checkBulletWithEnemyCollision() {
	auto it = mBulletList.begin();
	for (int i = 0; i < MAX_BULLETS && it != mBulletList.end(); i++) {
		auto it2 = mEnemyList.begin();
		for (int j = 0; j < MAX_ENEMYS && it2 != mEnemyList.end(); j++) {
			if ((it->getPos() - it2->getPos() == 0) || (it->getPos() - it2->getPos() == 1) || (it->getPos() - it2->getPos() == -1)) {
				mScore += 5;

				it2 = mEnemyList.erase(it2);
				it = mBulletList.erase(it);
				break;
			}
		}
	}
}

// This function checks if any bullet kills any point and erase both
void GameWorld::checkBulletWithPointCollision() {
	auto it = mBulletList.begin();
	for (int i = 0; i < MAX_BULLETS && it != mBulletList.end(); i++) {
		auto it2 = mPointList.begin();
		for (int j = 0; j < MAX_POINTS && it2 != mPointList.end(); j++) {
			if ((it->getPos() - it2->getPos() == 0) || (it->getPos() - it2->getPos() == 1) || (it->getPos() - it2->getPos() == -1)) {
				it2 = mPointList.erase(it2);
				it = mBulletList.erase(it);
				break;
			}
		}
	}
}

// This function erase the bullets out of limits
void GameWorld::eraseBulletsOutOfLimits() {
	auto it = mBulletList.begin();
	for (int i = 0; i < MAX_BULLETS && it != mBulletList.end(); i++) {
		if (it->getPos() > 80 || it->getPos() < 0) {
			it = mBulletList.erase(it);
		}
	}
}

// This function erase the points out of limits
void GameWorld::erasePointsOutOfLimits() {
	auto it = mPointList.begin();
	for (int i = 0; i < MAX_POINTS && it != mPointList.end(); i++) {
		if (it->getPos() > 80 || it->getPos() < 0) {
			it = mPointList.erase(it);
		}
	}
}

// This function erase the enemys out of limits
void GameWorld::eraseEnemysOutOfLimits() {
	auto it = mEnemyList.begin();
	for (int i = 0; i < MAX_ENEMYS && it != mEnemyList.end(); i++) {
		if (it->getPos() > 80 || it->getPos() < 0) {
			it = mEnemyList.erase(it);
		}
	}
}

// system(cls) stops the normal execution, this function cleans the sky
void GameWorld::cleanSky() {
	for (int sky = 0; sky < 3; sky++) {
		gotoxy(0, sky);
		for (int i = 0; i < MAP_SIZE; i++) {
			printf(" ");
		}
	}
}