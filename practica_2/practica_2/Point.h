class CPoint {
public:
	CPoint();

	CPoint(int pos, int dir);

	int  getPos ();
	int  getDir ();
	void setPos (int pos);
	void setDir (int dir);

private:
	int mPointPos;
	int mPointDir;
};