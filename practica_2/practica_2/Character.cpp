#include "stdafx.h"
#include "Character.h"

CCharacter::CCharacter() {
	mCharacterPos = 0;
	mLives = 3;
}

CCharacter::CCharacter(int pos) {
	mCharacterPos = pos;
	mLives = 3;
}

int  CCharacter::getPos   ()          { return mCharacterPos; }
int  CCharacter::getLives ()          { return mLives;        }
void CCharacter::setPos   (int pos)   { mCharacterPos = pos;  }
void CCharacter::setLives (int lives) { mLives = lives;       }