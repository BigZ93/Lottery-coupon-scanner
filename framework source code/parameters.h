//it calculates and stores values important for the image recognition process
#ifndef PARAMETERS_H
#define PARAMETERS_H
namespace scanner
{
class Parameters
{
private:
	//masking threshold
	int threshold;
	//parameters concerning markings
	int avgArea;
	int minArea;
	int maxArea;
	//parameters concerning coupon features
	int controlSquares;
	int maxSquares;
	int minSquares;
	int firstLineOfNum;
	int lastLineOfNum;
	//parameters used in finding positions of markings
	int xMargin;
	int yMargin;
	//constant ratios
	const double COUPON_TO_PHOTO_RATIO=0.578125;		//used for estimating coupon area
	const double MARKING_TO_COUPON_RATIO=0.0004066;		//used for finding marking area
	const double MARKING_AREA_MARGIN=0.1794871;			//used for finding limits of marking area
	const double COUPON_HEIGHT_TO_PHOTO_HEIGHT_RATIO=0.84375;		//used for estimating coupon height
	const double MARKING_HEIGHT_TO_COUPON_HEIGHT_RATIO=0.0092592;		//used for finding marking height and margin
	const double COUPON_WIDTH_TO_PHOTO_WIDTH_RATIO=0.6851851;		//used for finding coupon width
	const double PERSPECTIVE_DIFFERENCE_TO_COUPON_WIDTH_RATIO=0.0337837;	//used for finding margin
public:
	Parameters();
	int getThreshold() const;
	int getAvgArea() const;
	int getMinArea() const;
	int getMaxArea() const;
	int getXMargin() const;
	int getYMargin() const;
	int getControlSquares() const;
	int getMaxSquares() const;
	int getMinSquares() const;
	int getFirstLineOfNum() const;
	int getLastLineOfNum() const;
	void setThreshold(int x);
	void setAvgArea(int x);
	void calculateBoundaries(int size, int rows, int cols);
	void setControlSquares(int x);
	void setMaxSquares(int x);
	void setMinSquares(int x);
	void setFirstLineOfNum(int x);
	void setLastLineOfNum(int x);
};
}
#endif
