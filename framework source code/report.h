//prints all debug information
#ifndef REPORT_H
#define REPORT_H
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

namespace scanner
{
class Report
{
private:
	string msg;
public:
	Report();
	void show(ostream &os);
	template <class T> friend Report& operator<<(Report &rep, const T &val)
	{
		stringstream ss;
		ss<<val;
		rep.msg+=ss.str();
		return rep;
	}
};
}
#endif
