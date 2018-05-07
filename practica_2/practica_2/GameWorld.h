class GameWorld {
public:
	GameWorld();

	CCharacter            getCharacter             ();
	MeteorologicalManager getMeteorologicalManager ();
	std::list<CBullet>    getBulletsList           ();
	std::list<CEnemy>     getEnemysList            ();
	std::list<CPoint>     getPointsList            ();
	int                   getEnemyRespawnTime      ();
	int                   getPointRespawnTime      ();
	
	void setCharacter             (CCharacter character);
	void setMeteorologicalManager (MeteorologicalManager meteorologicalManager);
	void setBulletsList           (std::list<CBullet> bulletsList);
	void setEnemysList            (std::list<CEnemy> enemysList);
	void setPointsList            (std::list<CPoint> pointsList);
	void setEnemyRespawnTime      (int enemyRespawnTime);
	void setPointRespawnTime      (int enemyRespawnTime);

	void moveCharacterLeft();
	void moveCharacterRight();

	void shootLeft();
	void shootRight();

	void cleanSky();

	bool runGame          ();
	void generateElements ();
	void paintProcess     ();
	bool checkCollisions  ();
	void moveElements     ();
	
	void generateEnemy();
	void generatePoint();

	void checkBulletWithEnemyCollision();
	void checkBulletWithPointCollision();

	void eraseBulletsOutOfLimits ();
	void erasePointsOutOfLimits  ();
	void eraseEnemysOutOfLimits  ();

private:
	// Player character
	CCharacter mCharacter;

	MeteorologicalManager mMeteorologicalManager;

	// Point position
	std::list<CBullet>mBulletList;

	// Enemy position
	std::list<CEnemy>mEnemyList;

	// Point position
	std::list<CPoint>mPointList;

	// Enemy and point respawn time
	int mEnemyRespawnTime;
	int mPointRespawnTime;

	// Global score
	int mScore;
};