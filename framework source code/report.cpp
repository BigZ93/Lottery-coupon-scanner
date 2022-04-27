//prints all debug information
#include"report.h"

namespace scanner
{
Report::Report()
{
	msg="";
}
void Report::show(ostream &os)
{
	os<<msg;
}
}
