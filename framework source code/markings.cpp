//finds which blobs are markings on the coupon and represented numbers
#include"markings.h"
#include"distance.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

namespace scanner
{
Markings::Markings(cv::Mat &ccs, int &l, Parameters &par, int *ll, int *rl, Cpn &cpn, Report &r)
	:conCompStats(ccs),
	nrOfLabels(l),
	p(par),
	leftLine(ll),
	rightLine(rl),
	c(cpn),
	rep(r)
{
	a3=0;	//coefficients a & b of the horizontal line equation
	b3=0;
}
void Markings::marks()
{
	rep<<"normal markings--------------------------------------------------------\n";
	int i;
	int current;
	Cc blob;
	Distance tempDist;
	int counter=0;
	int j=0;
	for(i=p.getFirstLineOfNum(); i<p.getLastLineOfNum(); i++)	//checking if marking lies on horizontal line between 2 side squares but only for rows 2-42
	{
		lblob.calculateCoordinates(conCompStats.at<int>(leftLine[i], CC_STAT_WIDTH), conCompStats.at<int>(leftLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(leftLine[i], CC_STAT_LEFT), conCompStats.at<int>(leftLine[i], CC_STAT_TOP));	//calculating equation of horizontal line
		rblob.calculateCoordinates(conCompStats.at<int>(rightLine[i], CC_STAT_WIDTH), conCompStats.at<int>(rightLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(rightLine[i], CC_STAT_LEFT), conCompStats.at<int>(rightLine[i], CC_STAT_TOP));
		a3=(float) (rblob.getY()-lblob.getY())/(rblob.getX()-lblob.getX());
		b3=(float) rblob.getY()-(a3*rblob.getX());
		int maxDistance, xunit;
		maxDistance=rblob.getX()-lblob.getX();
		xunit=maxDistance/160;
		if(c.isFirstLineOfWager(i))
		{
			counter=0;
			j++;
		}
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
						counter++;	//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.find(i);
						rep<<"number- "<<r<<'\n';
						c.addNr(j, r);
					}
				}
				else
				{
					if(temp2-blob.getY()<p.getYMargin())
					{
						counter++;	//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.find(i);
						rep<<"number- "<<r<<'\n';
						c.addNr(j, r);
					}
				}
			}
			current++;
		}
	}
}

void Markings::marksh()
{
	rep<<"double horizontal markings--------------------------------------------------------\n";
	int i;
	int current;
	Cc blob;
	Distance tempDist;
	int counter=0;
	int j=0;
	for(i=p.getFirstLineOfNum(); i<p.getLastLineOfNum(); i++)
	{
		lblob.calculateCoordinates(conCompStats.at<int>(leftLine[i], CC_STAT_WIDTH), conCompStats.at<int>(leftLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(leftLine[i], CC_STAT_LEFT), conCompStats.at<int>(leftLine[i], CC_STAT_TOP));	//calculating equation of horizontal line
		rblob.calculateCoordinates(conCompStats.at<int>(rightLine[i], CC_STAT_WIDTH), conCompStats.at<int>(rightLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(rightLine[i], CC_STAT_LEFT), conCompStats.at<int>(rightLine[i], CC_STAT_TOP));
		a3=(float) (rblob.getY()-lblob.getY())/(rblob.getX()-lblob.getX());
		b3=(float) rblob.getY()-(a3*rblob.getX());
		int maxDistance, xunit;
		maxDistance=rblob.getX()-lblob.getX();
		xunit=maxDistance/160;
		if(c.isFirstLineOfWager(i))
		{
			counter=0;
			j++;
		}
		rep<<"a3: "<<a3<<" b3: "<<b3<<'\n';

		float temp2;		
		int r;
		current=1;
		while(current<nrOfLabels)
		{
			if(current==leftLine[i] || current==rightLine[i])
			{
				current++;
				continue;
			}
			blob.setArea(conCompStats.at<int>(current, CC_STAT_AREA));
			if(blob.getArea()>p.getMinArea()*2 && blob.getArea()<p.getMaxArea()*2.1 && blob.getArea()>p.getMaxArea())
			{
				blob.calculateCoordinates(conCompStats.at<int>(current, CC_STAT_WIDTH), conCompStats.at<int>(current, CC_STAT_HEIGHT), conCompStats.at<int>(current, CC_STAT_LEFT), conCompStats.at<int>(current, CC_STAT_TOP));

				temp2=a3*blob.getX()+b3;
				if(blob.getY()>=temp2)
				{
					if(blob.getY()-temp2<p.getYMargin())	//y of marking can differ by 10px
					{
						counter=counter+2;	//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.findH(i);
						rep<<"numbers- "<<r<<" & "<<r+1<<'\n';
						c.add2Nrs(j, r);
					}
				}
				else
				{
					if(temp2-blob.getY()<p.getYMargin())
					{
						counter=counter+2;	//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.findH(i);
						rep<<"numbers- "<<r<<" & "<<r+1<<'\n';
						c.add2Nrs(j, r);
					}
				}
			}
			current++;
		}
	}
}

void Markings::marksv()
{
	rep<<"double vertical markings--------------------------------------------------------\n";
	int i;
	int current;
	Cc blob;
	Distance tempDist;
	int counter=0;
	int j=0;
	int o;
	Cc lblob2;
	Cc rblob2;
	for(i=p.getFirstLineOfNum(); i<(p.getLastLineOfNum()-1); i++)	//checking if marking lies on horizontal line between 2 side squares but only for rows 2-41
	{
		lblob.calculateCoordinates(conCompStats.at<int>(leftLine[i], CC_STAT_WIDTH), conCompStats.at<int>(leftLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(leftLine[i], CC_STAT_LEFT), conCompStats.at<int>(leftLine[i], CC_STAT_TOP));	//calculating equation of horizontal line
		rblob.calculateCoordinates(conCompStats.at<int>(rightLine[i], CC_STAT_WIDTH), conCompStats.at<int>(rightLine[i], CC_STAT_HEIGHT), conCompStats.at<int>(rightLine[i], CC_STAT_LEFT), conCompStats.at<int>(rightLine[i], CC_STAT_TOP));
		lblob2.calculateCoordinates(conCompStats.at<int>(leftLine[i+1], CC_STAT_WIDTH), conCompStats.at<int>(leftLine[i+1], CC_STAT_HEIGHT), conCompStats.at<int>(leftLine[i+1], CC_STAT_LEFT), conCompStats.at<int>(leftLine[i+1], CC_STAT_TOP));
		rblob2.calculateCoordinates(conCompStats.at<int>(rightLine[i+1], CC_STAT_WIDTH), conCompStats.at<int>(rightLine[i+1], CC_STAT_HEIGHT), conCompStats.at<int>(rightLine[i+1], CC_STAT_LEFT), conCompStats.at<int>(rightLine[i+1], CC_STAT_TOP));
		o=(lblob2.getY()-lblob.getY())/2;
		lblob.setY(lblob.getY()+o);
		o=(rblob2.getY()-rblob.getY())/2;
		rblob.setY(rblob.getY()+o);
		a3=(float) (rblob.getY()-lblob.getY())/(rblob.getX()-lblob.getX());
		b3=(float) rblob.getY()-(a3*rblob.getX());
		int maxDistance, xunit;
		maxDistance=rblob.getX()-lblob.getX();
		xunit=maxDistance/160;
		if(c.isLastLineOfWager(i))
		{
			counter=0;
			j++;
			continue;
		}
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
			if(blob.getArea()>p.getMinArea()*2 && blob.getArea()<p.getMaxArea()*2.1 && blob.getArea()>p.getMaxArea())
			{
				blob.calculateCoordinates(conCompStats.at<int>(current, CC_STAT_WIDTH), conCompStats.at<int>(current, CC_STAT_HEIGHT), conCompStats.at<int>(current, CC_STAT_LEFT), conCompStats.at<int>(current, CC_STAT_TOP));
			
				temp2=a3*blob.getX()+b3;
				if(blob.getY()>=temp2)
				{
					if(blob.getY()-temp2<p.getYMargin())	//y of marking can differ by 10px
					{
						counter=counter+2;	//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.find(i);
						rep<<"numbers- "<<r<<" & "<<r+10<<'\n';
						c.add2NrsV(j, r);
					}
				}
				else
				{
					if(temp2-blob.getY()<p.getYMargin())
					{
						counter=counter+2;	//marking lies on the line, we're checking x and save result
						tempDist.setD((blob.getX()-lblob.getX())/xunit);
						rep<<"label "<<current<<"\ndistance "<<tempDist.getD()<<'\n';
						r=tempDist.find(i);
						rep<<"numbers- "<<r<<" & "<<r+10<<'\n';
						c.add2NrsV(j, r);
					}
				}
			}
			current++;
		}
	}
}
}
