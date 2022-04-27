//calculates distance of marking in units from left control line and from first row of wager
#include"distance.h"
#include"mycoupon.h"

namespace scanner
{
Distance::Distance()
	: lowerBoundary{21, 34, 49, 62, 76, 87, 101, 114, 128, 141, 155}, r(0), tempDist(0)	//small adjustment
{
	for(int lv : lowerBoundary)
	{
		upperBoundary.push_back(lv+7);	//small adjustment
	}
	for (int i=0; i<(int)lowerBoundary.size()-2; ++i)
	{
		lowerBoundaryH.push_back(lowerBoundary[i]+8);	//small adjustment
	}
	for (int lvh : lowerBoundaryH)
	{
		upperBoundaryH.push_back(lvh+4);
	}
}
void Distance::setD(int t)
{
	tempDist=t;
}
int Distance::getD() const
{
	return tempDist;
}
bool Distance::checkBoundaries(int i)
{
	return tempDist>=lowerBoundary[i] && tempDist<=upperBoundary[i];
}
bool Distance::checkBoundariesH(int i)
{
	return tempDist>=lowerBoundaryH[i] && tempDist<=upperBoundaryH[i];
}
int Distance::find(int i)
{
	r=0;
	for(int i=0; i<(int)lowerBoundary.size(); ++i)
	{
		if(checkBoundaries(i))
		{
			r=i+1;
			break;
		}
	}
	Cpn c;
	r=c.getMarkInLine(i, r);
	return r;
}
int Distance::findH(int i)
{
	r=0;
	for(int i=0; i<(int)lowerBoundaryH.size(); ++i)
	{
		if(checkBoundariesH(i))
		{
			r=i+1;
			break;
		}
	}
	Cpn c;
	r=c.getMarkInLine(i, r);
	return r;
}
}
