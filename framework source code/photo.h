//keeps information about image and control lines
#ifndef PHOTO_H
#define PHOTO_H
#include<vector>
#include<opencv2/core/core.hpp>

namespace scanner
{
class Photo
{
private:
	cv::Mat ccStats;
	int cols;
	int nrOfLabels;
public:
	Photo();
	Photo(cv::Mat ccs, int l, int c);
	cv::Mat getCcStats() const;
	int getNrOfLabels() const;
	int getNrOfCols() const;
};
}
#endif
