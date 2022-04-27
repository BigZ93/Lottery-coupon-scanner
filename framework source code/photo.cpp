//keeps information about image and control lines
#include"photo.h"
namespace scanner
{
Photo::Photo()
{
	nrOfLabels=0;
	cols=0;
}
Photo::Photo(cv::Mat ccs, int l, int c)
{
	ccStats=ccs;
	nrOfLabels=l;
	cols=c;
}
cv::Mat Photo::getCcStats() const
{
	return ccStats;
}
int Photo::getNrOfLabels() const
{
	return nrOfLabels;
}
int Photo::getNrOfCols() const
{
	return cols;
}
}
