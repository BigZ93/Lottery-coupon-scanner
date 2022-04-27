//calculates distance of marking in units from left control line and from first row of wager
#ifndef DISTANCE_H
#define DISTANCE_H
#include<vector>

namespace scanner
{
class Distance
{
private:
	int r;
	int tempDist;
	std::vector<int> lowerBoundary;
	std::vector<int> upperBoundary;
	std::vector<int> lowerBoundaryH;
	std::vector<int> upperBoundaryH;
public:
	Distance();
	void setD(int t);
	int getD() const;
	int find(int i);
	int findH(int i);
	bool checkBoundaries(int i);
	bool checkBoundariesH(int i);
};
}
#endif
