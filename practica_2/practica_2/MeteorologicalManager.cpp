#include "stdafx.h"
#include "PaintFunctions.h"
#include "Rain.h"
#include "MeteorologicalManager.h"

MeteorologicalManager::MeteorologicalManager() {
	mWaterDropList = std::list<CWaterDrop>(MAX_DROPS);
}

std::list<CWaterDrop> MeteorologicalManager::getWaterDropList ()                                    { return mWaterDropList;          }

void                  MeteorologicalManager::setWaterDropList (std::list<CWaterDrop> waterDropList) { mWaterDropList = waterDropList; }


void MeteorologicalManager::paintRainInSky() {
	for (auto it = mWaterDropList.begin(); it != mWaterDropList.end(); it++) {
		if (it->getStatus() == WATER_DROP_TOP_MAP) {
			gotoxy(it->getPos(), 0);
			printf("`");
		}
		else if (it->getStatus() == WATER_DROP_MID_MAP) {
			gotoxy(it->getPos(), 1);
			printf("|");
		}
		else if (it->getStatus() == WATER_DROP_BOT_MAP) {
			gotoxy(it->getPos(), 2);
			printf(".");
		}
	}
}

bool MeteorologicalManager::paintRainInWall(int pos) {
	for (auto it = mWaterDropList.begin(); it != mWaterDropList.end(); it++) {
		if (it->getStatus() == WATER_DROP_WALL) {
			if (it->getPos() == pos) {
				printf("v");
				return true;
			}
		}
	}

	return false;
}

void MeteorologicalManager::generateRain() {
	const int waterDropListSize = static_cast<int>(mWaterDropList.size());
	if (waterDropListSize < MAX_DROPS) {
		const int waterDropsToCreate = MAX_DROPS - waterDropListSize;

		for (int i = 0; i < waterDropsToCreate; i++) {
			int pos = rand() % 81;
			int status = WATER_DROP_TOP_MAP;

			CWaterDrop drop(pos, status);

			mWaterDropList.push_back(drop);
		}
	}
}

void MeteorologicalManager::updateRain() {
	for (auto it = mWaterDropList.begin(); it != mWaterDropList.end(); it++) {
		if (it->getStatus() == WATER_DROP_TOP_MAP) {
			it->setStatus(WATER_DROP_MID_MAP);
		}
		else if (it->getStatus() == WATER_DROP_MID_MAP) {
			it->setStatus(WATER_DROP_BOT_MAP);
		}
		else if (it->getStatus() == WATER_DROP_BOT_MAP) {
			it->setStatus(WATER_DROP_WALL);
		}
		else if (it->getStatus() == WATER_DROP_WALL) {
			it = mWaterDropList.erase(it);
		}
	}
}