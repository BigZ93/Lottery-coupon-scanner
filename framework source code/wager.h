//keeps information about single wager, it's status flags and adds a number(if good) to the result
#ifndef WAGER_H
#define WAGER_H
#include<vector>

namespace scanner
{
class Wager
{
private:
	int amount;
	std::vector<int> nr;
	bool correct;
	bool empty;
	bool cancel;
	int cancelValue;
public:
	Wager();
	~Wager();
	void addNr(int r);
	void add2Nrs(int r);
	void add2NrsV(int r);
	int getNr(int i) const;
	bool isCorrect() const;
	bool isEmpty() const;
	bool isCanceled() const;
	void sort();
	void setAmount(int a);
	void setCancelValue(int c);
};
}
#endif
