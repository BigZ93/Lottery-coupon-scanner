//keeps information about chosen coupon, deals with adding numbers to result
#include"mycoupon.h"
#include<algorithm>
#include<cassert>

using namespace std;

namespace scanner
{
Cpn::Cpn()
{
	results=new Wager[WAGER_COUNT];
	controlSquares=44;
	maxSquares=191;
	minSquares=91;
	firstLineOfNum=2;
	lastLineOfNum=42;
	nrOfModeLines=3;
	defaultNumbers=6;
	maxNumbers=12;
	modes=new int[MODES_COUNT];
	for(int i=0; i<3; i++)
	{
		modeLines[i]=0;
	}
	for(int i=0; i<MODES_COUNT; i++)
	{
		modes[i]=0;
	}
	firstLineOfWager[0]=7;
	firstLineOfWager[1]=12;
	firstLineOfWager[2]=17;
	firstLineOfWager[3]=22;
	firstLineOfWager[4]=27;
	firstLineOfWager[5]=32;
	firstLineOfWager[6]=37;
	linesOfWagers[0]=3;
	linesOfWagers[1]=8;
	linesOfWagers[2]=13;
	linesOfWagers[3]=18;
	linesOfWagers[4]=23;
	linesOfWagers[5]=28;
	linesOfWagers[6]=33;
	linesOfWagers[7]=38;
}
Cpn::~Cpn()
{
	delete[] results;
	delete[] modes;
}
void Cpn::setModeInLine(int i, int r)
{
	if(i==1 && r==3)
	{
		setMode(0, 1);
	}
	else if(i==1 && r==5)
	{
		setMode(1, 1);
	}
	else if(i==1 && r==7)
	{
		setMode(1, 2);
	}
	else if(i==42 && r!=1)
	{
		setMode(2, r-1);
	}
	else if(i==43 && (r==3 || r==4 || r==5 || r==6 || r==7 || r==8))
	{
		setMode(3, r+4);
	}
}
int Cpn::getIndex(int q) const
{
	assert(q>=0 && q<=2);
	int i;
	switch(q)
		{
		case 0:
			i=1;
			break;
		case 1:
			i=42;
			break;
		case 2:
			i=43;
			break;
		}
	return i;
}
int Cpn::getMarkInLine(int i, int r) const
{
	if(r>0 && searchForLine(i, 0))
	{
		r=r+10;
	}
	if(r>0 && searchForLine(i, 1))
	{
		r=r+20;
	}
	if(r>0 && searchForLine(i, 2))
	{
		r=r+30;
	}
	if(r>0 && searchForLine(i, 3))
	{
		r=r+40;
	}
	return r;
}
void Cpn::display(ostream &os)
{
	int i;
	int j;
	os<<endl;
	for(i=0; i<MODES_COUNT; i++)
	{
		os<<"option "<<i<<": "<<getMode(i)<<endl;
	}
	for(i=0; i<8; i++)
	{
		if(isCanceled(i)==true)
		{
			os<<"lottery "<<i+1<<" is cancelled"<<endl;
			continue;
		}
		if(isEmpty(i)==true)
		{
			os<<"lottery "<<i+1<<" is empty"<<endl;
				continue;
		}
		if(isCorrect(i)==false)
			{
			os<<"lottery "<<i+1<<" is filled wrongly"<<endl;
			continue;
		}
		else
		{
			sort(i);
			os<<"lottery "<<i+1<<": ";
			if(getMode(3)!=0)
			{
				for(j=0; j<getMode(3); j++)
				{
					os<<getNr(i, j)<<" ";
				}
			}
			else
			{
				for(j=0; j<6; j++)
				{
					os<<getNr(i, j)<<" ";
				}
			}
			os<<endl;
		}
	}
}
bool Cpn::isFirstLineOfWager(int i) const
{
	for(int j=0; j<WAGER_COUNT-1; j++)
	{
		if(i==firstLineOfWager[j])
		{
			return true;
		}
	}
	return false;
}
bool Cpn::isLastLineOfWager(int i) const
{
	for(int j=0; j<WAGER_COUNT-1; j++)
	{
		if(i==firstLineOfWager[j]-1)
		{
			return true;
		}
	}
	return false;
}
bool Cpn::searchForLine(int i, int offset) const
{
	for(int j=0; j<WAGER_COUNT; j++)
	{
		if(i==linesOfWagers[j]+offset)
		{
			return true;
		}
	}
	return false;
}
}
