#define WATER_DROP_TOP_MAP 0
#define WATER_DROP_MID_MAP 1
#define WATER_DROP_BOT_MAP 2
#define WATER_DROP_WALL    3

#define MAX_DROPS 20

#define MAP_SIZE 80

class MeteorologicalManager {
public:
	MeteorologicalManager::MeteorologicalManager();

	std::list<CWaterDrop> getWaterDropList();
	void setWaterDropList(std::list<CWaterDrop> waterDropList);

	void paintRainInSky  ();
	bool paintRainInWall (int pos);
	void generateRain    ();
	void updateRain      ();
private:
	std::list<CWaterDrop> mWaterDropList;
};
