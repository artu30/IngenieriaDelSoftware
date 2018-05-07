#include "stdafx.h"
#include "Enemy.h"

CEnemy::CEnemy() {
	mEnemyPos = 0;
	mEnemyDir = 0;
}

CEnemy::CEnemy(int pos, int dir) {
	mEnemyPos = pos;
	mEnemyDir = dir;
}

int  CEnemy::getPos ()        { return mEnemyPos; }
int  CEnemy::getDir ()        { return mEnemyDir; }
void CEnemy::setPos (int pos) { mEnemyPos = pos;  }
void CEnemy::setDir (int dir) { mEnemyDir = dir;  }