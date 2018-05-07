#include "stdafx.h"
#include "Rain.h"

CWaterDrop::CWaterDrop() {
	mDropPos = 0;
	mDropStatus = 0;
}

CWaterDrop::CWaterDrop(int pos, int status) {
	mDropPos = pos;
	mDropStatus = status;
}

int  CWaterDrop::getPos    ()           { return mDropPos;      }
int  CWaterDrop::getStatus ()           { return mDropStatus;   }
void CWaterDrop::setPos    (int pos)    { mDropPos = pos;       }
void CWaterDrop::setStatus (int status) { mDropStatus = status; }