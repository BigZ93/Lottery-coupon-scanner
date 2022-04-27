//keeps information about chosen coupon, deals with adding numbers to result
#ifndef MYCOUPON_H
#define MYCOUPON_H
#include"wager.h"
#include<iostream>
#include"basecoupon.h"
#include"photo.h"

namespace scanner
{
class Cpn : public GenericCpn
{
private:
	static const int WAGER_COUNT=8;
	static const int MODES_COUNT=4;
	int modeLines[3];
	int firstLineOfWager[7];
	int linesOfWagers[8];
public:
	Cpn();
	~Cpn();
	void setModeInLine(int i, int r);
	int getIndex(int q) const;
	int getMarkInLine(int i, int r) const;
	void display(std::ostream &os);
	bool isFirstLineOfWager(int i) const;
	bool isLastLineOfWager(int i) const;
	bool searchForLine(int i, int offset) const;
};
}
#endif
