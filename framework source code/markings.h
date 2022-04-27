//finds which blobs are markings on the coupon and represented numbers
#ifndef MARKINGS_H
#define MARKINGS_H
#include"parameters.h"
#include"ccomponent.h"
#include"wager.h"
#include"mycoupon.h"
#include"report.h"
#include<opencv2/core/core.hpp>

namespace scanner
{
class Markings
{
private:
	float a3;	//coefficients a & b of the horizontal line equation
	float b3;
	Cc lblob;
	Cc rblob;
	cv::Mat &conCompStats;
	int &nrOfLabels;
	Parameters &p;
	int *leftLine;
	int *rightLine;
	Cpn &c;
	Report &rep;
public:
	Markings(cv::Mat &ccs, int &l, Parameters &par, int *ll, int *rl, Cpn &cpn, Report &r);
	void marks();
	void marksv();
	void marksh();
};
}
#endif
