#include<iostream>
#include<string>
#include"scanner.h"
#include"mycoupon.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace scanner;
using namespace cv;

int main()
{
	string n;
	cout<<"name a picture to open"<<endl;
	cin>>n;
	//string n="test.jpg";
	int d=1;
	Mat o;
	o=imread(n, 1);
	Cpn c;
	Cpn &cc=c;
	//analyze(n, cc, d);
	analyze(o, cc, d);
	return 0;
}
