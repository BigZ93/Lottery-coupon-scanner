//establishes which markings belong to control columns on sides of the coupon
#ifndef CONTROLLINES_H
#define CONTROLLINES_H
#include"parameters.h"
#include"ccomponent.h"
#include"report.h"
#include"photo.h"
#include<opencv2/core/core.hpp>

namespace scanner
{
class ControlLines
{
private:
	float a1;
	float a2;
	float b1;
	float b2;
	Cc blob1;
	Cc blob2;
	Cc lblob;
	Cc rblob;
public:
	ControlLines();
	void left(Photo &pt, Parameters &p, Report &rep, int *leftLine);
	void right(Photo &pt, Parameters &p, Report &rep, int *rightLine);
	void fill(Photo &pt, Parameters &p, int *leftLine, int *rightLine);
	bool checkLeftLine(int x1, int x2, int margin);
	bool checkRightLine(int x1, int x2, int margin);
	bool checkLines(int x1, int x2, int margin, int i, int max);
};
}
#endif
