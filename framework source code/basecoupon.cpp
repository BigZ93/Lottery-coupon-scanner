//generic coupon base class
#include"basecoupon.h"

namespace scanner
{
void GenericCpn::addNr(int i, int r)
{
	results[i].addNr(r);
}
void GenericCpn::add2Nrs(int i, int r)
{
	results[i].add2Nrs(r);
}
void GenericCpn::add2NrsV(int i, int r)
{
	results[i].add2NrsV(r);
}
int GenericCpn::getNr(int i, int j) const
{
	return results[i].getNr(j);
}
bool GenericCpn::isCorrect(int i) const
{
	return results[i].isCorrect();
}
bool GenericCpn::isEmpty(int i) const
{
	return results[i].isEmpty();
}
bool GenericCpn::isCanceled(int i) const
{
	return results[i].isCanceled();
}
void GenericCpn::sort(int i)
{
	results[i].sort();
}
void GenericCpn::setAmount(int i, int a)
{
	results[i].setAmount(a);
}
void GenericCpn::setMode(int i, int x)
{
	modes[i]=x;
}
int GenericCpn::getMode(int i) const
{
	return modes[i];
}
int GenericCpn::getControlSquares() const
{
	return controlSquares;
}
int GenericCpn::getMaxSquares() const
{
	return maxSquares;
}
int GenericCpn::getMinSquares() const
{
	return minSquares;
}
int GenericCpn::getFirstLineOfNum() const
{
	return firstLineOfNum;
}
int GenericCpn::getLastLineOfNum() const
{
	return lastLineOfNum;
}
int GenericCpn::getNrOfModeLines() const
{
	return nrOfModeLines;
}
int GenericCpn::getDefaultNumbers() const
{
	return defaultNumbers;
}
int GenericCpn::getMaxNumbers() const
{
	return maxNumbers;
}
void GenericCpn::setPhoto(Photo p)
{
	pt=p;
}
Photo GenericCpn::getPhoto() const
{
	return pt;
}
}
