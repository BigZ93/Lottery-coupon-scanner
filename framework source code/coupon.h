class GenericCpn
{
private:
	Wager results;
	int modes;
public:
	virtual void addNr(int i, int r);
	virtual void add2Nrs(int i, int r);
	virtual void add2NrsV(int i, int r);
	virtual int getNr(int i, int j);
	virtual bool getCorrect(int i);
	virtual bool getEmpty(int i);
	virtual bool getCancel(int i);
	virtual void sort(int i);
	virtual void setAmount(int i, int a);
	virtual void setMode(int i, int x);
	virtual int getMode(int i);
};
