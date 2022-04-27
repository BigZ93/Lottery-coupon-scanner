//checks which modes are chosen by user
#include"modes.h"
#include"distance.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

namespace scanner
{
Modes::Modes()
{
	a3=0;	//coefficients a & b of the horizontal line equation
	b3=0;
}
void Modes::checkModes(Mat conCompStats, int nrOfLabels, Parameters &p, int *leftLine, int *rightLine, Cpn &c, Report &rep)
{
	rep<<"options--------------------------------------------------------\n";
	Distance tempDist;
	int i;
	int current;
	Cc blob;
	int j=0;
	for(int q=0; q<c.getNrOfModeLines(); q++)	//checking if marking lies on horizontal line between 2 side squares but only for rows 1, 42 and 43
	{
		i=c.getIndex(q);
		lblob.calculateCoordinates(conCompStats.at<int>(leftLine[i], CC_STAT_WIDTH), conCompStats.at<int>(leftLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(leftLine[i], CC_STAT_LEFT), conCompStats.at<int>(leftLine[i], CC_STAT_TOP));	//calculating equation of horizontal line
		rblob.calculateCoordinates(conCompStats.at<int>(rightLine[i], CC_STAT_WIDTH), conCompStats.at<int>(rightLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(rightLine[i], CC_STAT_LEFT), conCompStats.at<int>(rightLine[i], CC_STAT_TOP));
		a3=(float) (rblob.getY()-lblob.getY())/(rblob.getX()-lblob.getX());
		b3=(float) rblob.getY()-(a3*rblob.getX());
		int maxDistance, xunit;
		maxDistance=rblob.getX()-lblob.getX();
		xunit=maxDistance/160;
		rep<<"a3: "<<a3<<" b3: "<<b3<<'\n';

		float temp2;
		current=1;
		int r;
		while(current<nrOfLabels)
		{
			if(current==leftLine[i] || current==rightLine[i])
			{
				current++;
				continue;
			}
			blob.setArea(conCompStats.at<int>(current, CC_STAT_AREA));
			if(blob.getArea()>p.getMinArea() && blob.getArea()<p.getMaxArea())
			{
				blob.calculateCoordinates(conCompStats.at<int>(current, CC_STAT_WIDTH), conCompStats.at<int>(current, CC_STAT_HEIGHT), conCompStats.at<int>(current, CC_STAT_LEFT), conCompStats.at<int>(current, CC_STAT_TOP));

				temp2=a3*blob.getX()+b3;
				if(blob.getY()>=temp2)
				{
					if(blob.getY()-temp2<p.getYMargin())	//y of marking can differ by 10px
					{
						//marking lies on the line, we're checking x and save result						
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.find(0);
						rep<<"field "<<r<<'\n';
						c.setModeInLine(i, r);
					}
				}
				else
				{
					if(temp2-blob.getY()<p.getYMargin())
					{
						//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.find(0);
						rep<<"field "<<r<<'\n';
						c.setModeInLine(i, r);
					}
				}
			}
			current++;
		}
	}
	if(c.getMode(3)!=0)
	{
		for(int i=0; i<8; i++)
		{
			c.setAmount(i, c.getMode(3));
		}
	}
}
}
