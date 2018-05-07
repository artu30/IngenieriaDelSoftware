#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet() {
	mBulletPos = 0;
	mBulletDir = 0;
}

CBullet::CBullet(int pos, int dir) {
	mBulletPos = pos;
	mBulletDir = dir;
}

int  CBullet::getPos ()        { return mBulletPos; }
int  CBullet::getDir ()        { return mBulletDir; }
void CBullet::setPos (int pos) { mBulletPos = pos;  }
void CBullet::setDir (int dir) { mBulletDir = dir;  }