class CBullet {
public:
	CBullet();

	CBullet(int pos, int dir);

	int  getPos ();
	int  getDir ();
	void setPos (int pos);
	void setDir (int dir);

private:
	int mBulletPos;
	int mBulletDir;
};