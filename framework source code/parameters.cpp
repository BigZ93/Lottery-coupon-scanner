//it calculates and stores values important for the image recognition process
#include"parameters.h"
#include<cassert>

namespace scanner
{
Parameters::Parameters()
{
	threshold=0;
	avgArea=0;
	minArea=0;
	maxArea=0;
	xMargin=0;
	yMargin=0;
	controlSquares=0;
	maxSquares=0;
	minSquares=0;
	firstLineOfNum=0;
	lastLineOfNum=0;
}
int Parameters::getThreshold() const
{
	return threshold;
}
int Parameters::getAvgArea() const
{
	return avgArea;
}
int Parameters::getMinArea() const
{
	return minArea;
}
int Parameters::getMaxArea() const
{
	return maxArea;
}
int Parameters::getXMargin() const
{
	return xMargin;
}
int Parameters::getYMargin() const
{
	return yMargin;
}
int Parameters::getControlSquares() const
{
	return controlSquares;
}
int Parameters::getMaxSquares() const
{
	return maxSquares;
}
int Parameters::getMinSquares() const
{
	return minSquares;
}
int Parameters::getFirstLineOfNum() const
{
	return firstLineOfNum;
}
int Parameters::getLastLineOfNum() const
{
	return lastLineOfNum;
}
void Parameters::setThreshold(int x)
{
	threshold=x;
}
void Parameters::setAvgArea(int x)
{
	avgArea=x;
}
void Parameters::calculateBoundaries(int size, int rows, int cols)
{
	assert(size>0);
	double couponArea=size*COUPON_TO_PHOTO_RATIO;
	double markingArea=couponArea*MARKING_TO_COUPON_RATIO;
	double markingBoundary=markingArea*MARKING_AREA_MARGIN;
	minArea=markingArea-markingBoundary-400;	//~1600	//small adjustment
	maxArea=markingArea+markingBoundary+900;	//~2300	//small adjustment
	double couponH=rows*COUPON_HEIGHT_TO_PHOTO_HEIGHT_RATIO;
	double markingH=couponH*MARKING_HEIGHT_TO_COUPON_HEIGHT_RATIO;
	yMargin=(markingH/3)+1;	//~10	//small adjustment
	double couponW=cols*COUPON_WIDTH_TO_PHOTO_WIDTH_RATIO;
	xMargin=couponW*PERSPECTIVE_DIFFERENCE_TO_COUPON_WIDTH_RATIO;	//~50
}
void Parameters::setControlSquares(int x)
{
	controlSquares=x;
}
void Parameters::setMaxSquares(int x)
{
	maxSquares=x;
}
void Parameters::setMinSquares(int x)
{
	minSquares=x;
}
void Parameters::setFirstLineOfNum(int x)
{
	firstLineOfNum=x;
}
void Parameters::setLastLineOfNum(int x)
{
	lastLineOfNum=x;
}
}
