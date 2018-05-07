#include "stdafx.h"
#include "Point.h"

CPoint::CPoint() {
	mPointPos = 0;
	mPointDir = 0;
}

CPoint::CPoint(int pos, int dir) {
	mPointPos = pos;
	mPointDir = dir;
}

int  CPoint::getPos ()        { return mPointPos; }
int  CPoint::getDir ()        { return mPointDir; }
void CPoint::setPos (int pos) { mPointPos = pos;  }
void CPoint::setDir (int dir) { mPointDir = dir;  }