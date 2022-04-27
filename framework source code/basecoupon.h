//generic coupon base class
#ifndef BASECOUPON_H
#define BASECOUPON_H
#include"wager.h"
#include<iostream>
#include"photo.h"

namespace scanner
{
class GenericCpn
{
protected:
	Wager *results;
	int *modes;
	int controlSquares;
	int maxSquares;
	int minSquares;
	int firstLineOfNum;
	int lastLineOfNum;
	int nrOfModeLines;
	int defaultNumbers;
	int maxNumbers;
	Photo pt;
public:
	virtual void addNr(int i, int r);
	virtual void add2Nrs(int i, int r);
	virtual void add2NrsV(int i, int r);
	virtual int getNr(int i, int j) const;
	virtual bool isCorrect(int i) const;
	virtual bool isEmpty(int i) const;
	virtual bool isCanceled(int i) const;
	virtual void sort(int i);
	virtual void setAmount(int i, int a);
	virtual void setMode(int i, int x);
	virtual int getMode(int i) const;
	virtual int getControlSquares() const;
	virtual int getMaxSquares() const;
	virtual int getMinSquares() const;
	virtual int getFirstLineOfNum() const;
	virtual int getLastLineOfNum() const;
	virtual int getNrOfModeLines() const;
	virtual void setModeInLine(int i, int r)=0;
	virtual int getIndex(int q) const=0;
	virtual int getMarkInLine(int i, int r) const=0;
	virtual void display(std::ostream &os)=0;
	virtual bool isFirstLineOfWager(int i) const=0;
	virtual bool isLastLineOfWager(int i) const=0;
	virtual int getDefaultNumbers() const;
	virtual int getMaxNumbers() const;
	virtual bool searchForLine(int i, int offset) const=0;
	virtual void setPhoto(Photo p);
	virtual Photo getPhoto() const;
};
}
#endif
