class CWaterDrop {
public:
	CWaterDrop();

	CWaterDrop(int pos, int status);

	int  getPos    ();
	int  getStatus ();

	void setPos    (int pos);
	void setStatus (int status);

private:
	int mDropPos;
	int mDropStatus;
};