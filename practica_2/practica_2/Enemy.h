class CEnemy {
public:
	CEnemy();

	CEnemy(int pos, int dir);

	int  getPos ();
	int  getDir ();
	void setPos (int pos);
	void setDir (int dir);

private:
	int mEnemyPos;
	int mEnemyDir;
};