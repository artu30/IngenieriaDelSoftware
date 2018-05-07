class CCharacter {
public:
	CCharacter();

	CCharacter(int pos);

	int  getPos   ();
	int  getLives ();
	void setPos   (int pos);
	void setLives (int lives);

private:
	int mCharacterPos;
	int mLives;
};
