//main function
#include"scanner.h"
#include"mycoupon.h"
#include"distance.h"
#include"controllines.h"
#include"markings.h"
#include"modes.h"
#include<iostream>
#include"report.h"
#include"photo.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<fstream>

using namespace cv;
using namespace std;

namespace scanner
{
int analyze(cv::Mat obrazBGR, Cpn &c, int debug)
{
	//Mat obrazBGR;
	//obrazBGR=imread(nazwaObrazu, 1);
	Report rep;
	if(obrazBGR.data==NULL)
	{
		rep<<"No image data\n";
		if(debug!=0)
		{
			rep.show(cout);
		}
		return -1;
	}
	Parameters p;
	ifstream file("cfg.txt");
	if(file)
	{
		int tmp;
		file>>tmp;
		p.setThreshold(tmp);
	}
	else
	{
		p.setThreshold(80);	//40~80
	}
	rep<<"Threshold: "<<p.getThreshold()<<'\n';
	Mat obrazHSV;		//convertion from hsv
	cvtColor(obrazBGR, obrazHSV, CV_BGR2HSV);
	if(debug!=0)
	{
		imwrite("./testHSV.jpg", obrazHSV);
	}
	Mat kanalyHSV[3];
	split(obrazHSV, kanalyHSV);
	Mat obrazSzaryHSV;
	obrazSzaryHSV=kanalyHSV[2];
	if(debug!=0)
	{
		imwrite("./testSzaryHSV.jpg", obrazSzaryHSV);
	}
	Mat obrazMaskaHSV;
	threshold(obrazSzaryHSV, obrazMaskaHSV, p.getThreshold(), 255, THRESH_BINARY_INV);
	if(debug!=0)
	{
		imwrite("./testMaskaHSV.jpg", obrazMaskaHSV);
	}

	int size=(obrazMaskaHSV.rows*obrazMaskaHSV.cols);
	rep<<"image size: "<<size<<'\n';
	int nrOfLabels;
	Mat conCompLabels;	//connected components
	Mat conCompStats;
	Mat conCompCentroid;
	nrOfLabels=connectedComponentsWithStats(obrazMaskaHSV, conCompLabels, conCompStats, conCompCentroid, 8, CV_32S);
	rep<<"total labels: "<<nrOfLabels<<'\n';
	p.calculateBoundaries(size, obrazMaskaHSV.rows, obrazMaskaHSV.cols);
	p.setControlSquares(c.getControlSquares());
	p.setMaxSquares(c.getMaxSquares());
	p.setMinSquares(c.getMinSquares());
	p.setFirstLineOfNum(c.getFirstLineOfNum());
	p.setLastLineOfNum(c.getLastLineOfNum());
	int area;
	int i;
	int z, z2;
	int avgArea=0;
	int squares=0;
	int bigSquares=0;
	for(i=1; i<nrOfLabels; i++)
	{
		area=conCompStats.at<int>(i, CC_STAT_AREA);
		if(area>p.getMinArea() && area<p.getMaxArea())
		{
			z=conCompStats.at<int>(i, CC_STAT_LEFT);
			z2=conCompStats.at<int>(i, CC_STAT_TOP);
			rep<<i<<": "<<area<<" LEFT px: "<<z<<" TOP px: "<<z2<<'\n';
			squares++;
			avgArea=avgArea+area;
		}
		if(area>p.getMinArea()*2 && area<p.getMaxArea()*2.1 && area>p.getMaxArea())
		{
			z=conCompStats.at<int>(i, CC_STAT_LEFT);
			z2=conCompStats.at<int>(i, CC_STAT_TOP);
			rep<<"big "<<i<<": "<<area<<" LEFT px: "<<z<<" TOP px: "<<z2<<'\n';
			bigSquares++;
			avgArea=avgArea+area;
		}
	}
	rep<<"squares found: "<<squares<<"\ndouble squares found: "<<bigSquares<<'\n';	//will be 91-191
	if((squares+(bigSquares*2))<p.getMinSquares() || (squares+(bigSquares*2))>p.getMaxSquares())	//checking number of squares
	{
		rep<<"recognized wrong number of marked squares\ntake new photo\n";
		rep.show(cout);
		return 0;
	}
	p.setAvgArea(avgArea=avgArea/(squares+(bigSquares*2)));
	rep<<"average area of square: "<<p.getAvgArea()<<'\n'<<'\n';
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//looking for equation of straight line a=(y2-y1)/(x2-x1)  b=y1-a*x1	a1, b1 for left vertical, a2, b2 for right vertical, a3, b3 for horizontal
	Report &r=rep;
	int leftLine[p.getControlSquares()];
	int rightLine[p.getControlSquares()];
	Parameters &t1=p;
	Photo pt(conCompStats, nrOfLabels, obrazMaskaHSV.cols);
	c.setPhoto(pt);
	Photo &t2=pt;
	int *ll=leftLine;
	int *rl=rightLine;
	ControlLines temp;
	temp.left(t2, t1, r, ll);
	temp.right(t2, t1, r, rl);
	temp.fill(t2, t1, ll, rl);
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//checking extra options
	Cpn &cc=c;
	Modes temp2;
	temp2.checkModes(conCompStats, nrOfLabels, t1, ll, rl, cc, r);
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//distance between markings=0.5 of marking
//4mm, 2mm, side square <-> marking 7.5mm = 1.875 of square
//distance between side columns is 8cm => 160 units
	Markings temp3(conCompStats, nrOfLabels, t1, ll, rl, cc, r);
	temp3.marks();
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//searching for double vertical markings
	temp3.marksv();
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//searching for double horizontal markings
//distance between border lines is 1.3 cm =>26 units
	temp3.marksh();
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//showing results
	if(debug!=0)
	{
		rep.show(cout);
		c.display(cout);
	}
	return 0;
}
}
