//main function
#ifndef SCANNER_H
#define SCANNER_H
#include<string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"mycoupon.h"

namespace scanner
{
	int analyze(cv::Mat obrazBGR, Cpn &c, int debug);
}
#endif
