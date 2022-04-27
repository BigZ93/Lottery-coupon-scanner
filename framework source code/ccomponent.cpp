//keeps basic information about a connected component
#include"ccomponent.h"

namespace scanner
{
Cc::Cc()
{
	area=0;
	w=0;
	h=0;
	x=0;
	y=0;
}
void Cc::setArea(int t)
{
	area=t;
}
void Cc::setX(int t)
{
	x=t;
}
void Cc::setY(int t)
{
	y=t;
}
int Cc::getArea() const
{
	return area;
}
int Cc::getW() const
{
	return w;
}
int Cc::getH() const
{
	return h;
}
int Cc::getX() const
{
	return x;
}
int Cc::getY() const
{
	return y;
}
void Cc::calculateCoordinates(int width, int height, int leftP, int topP)
{
	w=(width+1)/2;		//half of width
	h=(height+1)/2;		//half of height
	x=leftP+w;		//centre x
	y=topP+h;		//centre y
}
}
