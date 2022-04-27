//establishes which markings belong to control columns on sides of the coupon
#include"controllines.h"
#include"distance.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

namespace scanner
{
ControlLines::ControlLines()
{
	a1=0;
	a2=0;
	b1=0;
	b2=0;
}
void ControlLines::left(Photo &pt, Parameters &p, Report &rep, int *leftLine)
{
	Mat conCompStats=pt.getCcStats();
	int i=1;
	int current;
	while(i<pt.getNrOfLabels())	//top left square
	{
		blob1.setArea(conCompStats.at<int>(i, CC_STAT_AREA));
		if(blob1.getArea()>p.getMinArea() && blob1.getArea()<p.getMaxArea())
		{
			blob1.calculateCoordinates(conCompStats.at<int>(i, CC_STAT_WIDTH), conCompStats.at<int>(i, CC_STAT_HEIGHT), conCompStats.at<int>(i, CC_STAT_LEFT), conCompStats.at<int>(i, CC_STAT_TOP));
			current=i;
			if(blob1.getX()<pt.getNrOfCols()/3)
			{
				rep<<"label: "<<i<<'\n';
				break;
			}
			
		}
		i++;
	}
	rep<<"left x1: "<<blob1.getX()<<" y1: "<<blob1.getY()<<'\n';
	leftLine[0]=i;
	i=pt.getNrOfLabels();
	while(i>0)	//bottom left square
	{
		blob2.setArea(conCompStats.at<int>(i, CC_STAT_AREA));
		if(blob2.getArea()>p.getMinArea() && blob2.getArea()<p.getMaxArea())
		{
			blob2.calculateCoordinates(conCompStats.at<int>(i, CC_STAT_WIDTH), conCompStats.at<int>(i, CC_STAT_HEIGHT), conCompStats.at<int>(i, CC_STAT_LEFT), conCompStats.at<int>(i, CC_STAT_TOP));
			if(checkLeftLine(blob1.getX(), blob2.getX(), p.getXMargin()))	//x2 can be dislocated from vertical line by 50 px max
			{
				rep<<"label: "<<i<<'\n';
				break;
			}
		}
		i--;
	}
	rep<<"left x2: "<<blob2.getX()<<" y2: "<<blob2.getY()<<'\n';
	leftLine[p.getControlSquares()-1]=i;
	a1=(float) (blob2.getY()-blob1.getY())/(blob2.getX()-blob1.getX());
	b1=(float) blob1.getY()-(a1*blob1.getX());
	rep<<"a1: "<<a1<<" b1: "<<b1<<'\n'<<'\n';
}

void ControlLines::right(Photo &pt, Parameters &p, Report &rep, int *rightLine)
{
	string s;
	stringstream ss, ss2;
	Mat conCompStats=pt.getCcStats();
	int i=pt.getNrOfLabels();
	int current;
	while(i>0)	//bottom right square
	{
		blob2.setArea(conCompStats.at<int>(i, CC_STAT_AREA));
		if(blob2.getArea()>p.getMinArea() && blob2.getArea()<p.getMaxArea())
		{
			blob2.calculateCoordinates(conCompStats.at<int>(i, CC_STAT_WIDTH), conCompStats.at<int>(i, CC_STAT_HEIGHT), conCompStats.at<int>(i, CC_STAT_LEFT), conCompStats.at<int>(i, CC_STAT_TOP));
			if(blob2.getX()>(pt.getNrOfCols()*2)/3)
			{
				rep<<"label: "<<i<<'\n';
				break;
			}
		}
		i--;
	}
	rep<<"right x2: "<<blob2.getX()<<" y2: "<<blob2.getY()<<'\n';
	rightLine[p.getControlSquares()-1]=i;
	i=1;
	while(i<pt.getNrOfLabels())	//top right square
	{
		blob1.setArea(conCompStats.at<int>(i, CC_STAT_AREA));
		if(blob1.getArea()>p.getMinArea() && blob1.getArea()<p.getMaxArea())
		{
			blob1.calculateCoordinates(conCompStats.at<int>(i, CC_STAT_WIDTH), conCompStats.at<int>(i, CC_STAT_HEIGHT), conCompStats.at<int>(i, CC_STAT_LEFT), conCompStats.at<int>(i, CC_STAT_TOP));
			rep<<"label: "<<i<<'\n';
			current=i;
			if(checkRightLine(blob2.getX(), blob1.getX(), p.getXMargin()))	//x1 can be dislocated from vertical line by 50 px max
			{
				continue;
			}
			break;
		}
		i++;
	}
	rep<<"right x1: "<<blob1.getX()<<" y1: "<<blob1.getY()<<'\n';
	rightLine[0]=i;
	a2=(float) (blob2.getY()-blob1.getY())/(blob2.getX()-blob1.getX());
	b2=(float) blob1.getY()-(a1*blob1.getX());
	rep<<"a2: "<<a2<<" b2: "<<b2<<'\n'<<'\n';
}

void ControlLines::fill(Photo &pt, Parameters &p, int *leftLine, int *rightLine)
{
	Mat conCompStats=pt.getCcStats();
	int i=1;
	int leftSqIndex=0;
	int rightSqIndex=0;
	Cc blob;
	lblob.calculateCoordinates(conCompStats.at<int>(leftLine[0], CC_STAT_WIDTH), conCompStats.at<int>(leftLine[0], CC_STAT_HEIGHT), conCompStats.at<int>(leftLine[0], CC_STAT_LEFT), conCompStats.at<int>(leftLine[0], CC_STAT_TOP));
	rblob.calculateCoordinates(conCompStats.at<int>(rightLine[0], CC_STAT_WIDTH), conCompStats.at<int>(rightLine[0], CC_STAT_HEIGHT), conCompStats.at<int>(rightLine[0], CC_STAT_LEFT), conCompStats.at<int>(rightLine[0], CC_STAT_TOP));
	while(i<pt.getNrOfLabels())	//searching for squares lying on side lines
	{
		blob.setArea(conCompStats.at<int>(i, CC_STAT_AREA));
		if(blob.getArea()>p.getMinArea() && blob.getArea()<p.getMaxArea())
		{
			blob.calculateCoordinates(conCompStats.at<int>(i, CC_STAT_WIDTH), conCompStats.at<int>(i, CC_STAT_HEIGHT), conCompStats.at<int>(i, CC_STAT_LEFT), conCompStats.at<int>(i, CC_STAT_TOP));
			if(checkLines(blob.getX(), lblob.getX(), p.getXMargin(), leftSqIndex, p.getControlSquares()))
			{
				if(leftLine[leftSqIndex]!=i)
				{
					leftLine[leftSqIndex]=i;
					leftSqIndex++;
				}
				else
				{
					leftSqIndex++;
				}
			}
			else if(checkLines(blob.getX(), rblob.getX(), p.getXMargin(), rightSqIndex, p.getControlSquares()))
			{
				if(rightLine[rightSqIndex]!=i)
				{
					rightLine[rightSqIndex]=i;
					rightSqIndex++;
				}
				else
				{
					rightSqIndex++;
				}
			}
		}
		i++;
	}
}
bool ControlLines::checkLeftLine(int x1, int x2, int margin)
{
	if(x2>(x1-margin) && x2<(x1+margin))
	{
		return true;
	}
	return false;
}
bool ControlLines::checkRightLine(int x1, int x2, int margin)
{
	if(x1<(x2-margin) && x1>(x2+margin))
	{
		return true;
	}
	return false;
}
bool ControlLines::checkLines(int x1, int x2, int margin, int i, int max)
{
	if(x1>(x2-margin) && x1<(x2+margin) && i<max)
	{
		return true;
	}
	return false;
}
}
