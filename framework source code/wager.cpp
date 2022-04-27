//keeps information about single wager, it's status flags and adds a number(if good) to the result
#include"wager.h"
#include<algorithm>

using namespace std;

namespace scanner
{
Wager::Wager()
{
	amount=6;
	cancelValue=50;
	correct=false;
	empty=true;
	cancel=false;
}
Wager::~Wager()
{
}
void Wager::addNr(int r)
{
	if(r==cancelValue)
	{
		cancel=true;
		return;
	}
	if(nr.size()==amount || r==0)
	{
		correct=false;
		return;
	}
	nr.push_back(r);
	empty=false;
	if(nr.size()==amount)
	{
		correct=true;
	}
}
void Wager::add2Nrs(int r)
{
	if(r==cancelValue-1)
	{
		cancel=true;
		return;
	}
	if(nr.size()==amount || nr.size()==amount-1 || r==0)
	{
		correct=false;
		return;
	}
	nr.push_back(r);
	nr.push_back(r+1);
	empty=false;
	if(nr.size()==amount)
	{
		correct=true;
	}
}
void Wager::add2NrsV(int r)	// \\r==0
{
	if(r==cancelValue-10)
	{
		cancel=true;
		return;
	}
	if(nr.size()==amount || nr.size()==amount-1 || r==0)
	{
		correct=false;
		return;
	}
	nr.push_back(r);
	nr.push_back(r+1);
	empty=false;
	if(nr.size()==amount)
	{
		correct=true;
	}
}
int Wager::getNr(int i) const
{
	return nr[i];
}
bool Wager::isCorrect() const
{
	return correct;
}
bool Wager::isEmpty() const
{
	return empty;
}
bool Wager::isCanceled() const
{
	return cancel;
}
void Wager::sort()
{
	std::sort(nr.begin(), nr.end());
}
void Wager::setAmount(int a)
{
	amount=a;
}
void Wager::setCancelValue(int c)
{
	cancelValue=c;
}
}
