//keeps basic information about a connected component
#ifndef CCOMPONENT_H
#define CCOMPONENT_H
namespace scanner
{
class Cc
{
private:
	int area;
	int w;
	int h;
	int x;
	int y;
public:
	Cc();
	void setArea(int t);
	void setX(int t);
	void setY(int t);
	int getArea() const;
	int getW() const;
	int getH() const;
	int getX() const;
	int getY() const;
	void calculateCoordinates(int width, int height, int leftP, int topP);
};
}
#endif
