//checks which modes are chosen by user
#ifndef MODES_H
#define MODES_H
#include"parameters.h"
#include"wager.h"
#include"ccomponent.h"
#include"mycoupon.h"
#include"report.h"
#include<opencv2/core/core.hpp>

namespace scanner
{
class Modes
{
private:
	float a3;	//coefficients a & b of the horizontal line equation
	float b3;
	Cc lblob;
	Cc rblob;
public:
	Modes();
	void checkModes(cv::Mat conCompStats, int nrOfLabels, Parameters &p, int *leftLine, int *rightLine, Cpn &c, Report &rep);
};
}
#endif
