#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <ctime>
#include <stack>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

double pi=3.1415926;
int main()
{
	double length=1;
	double q=1;
	clock_t s, e;
	while(length)
	{
		cin>>length>>q;
	    s=clock();
	    double t=sqrt(3);
	    double X=length/2/t;
	    double dis2=length*length/24;//dis*dis
	    double d=0.00001;//dx或dy长度
	    double d2=0.0000000001;//dxdy
	    double sum=0;//sum为对1/〖(〖dis〗^2+x^2+y^2)〗^(3/2)的积分
	    for(double x=0;x<X;x+=d)//先对y积分再对x积分
	    {
	        double k=t*x;//当x确定时，y的积分长度
	        double x2=x*x;//保存x^2的值，减少运算
	        for(double y=0;y<k;y+=d)
	        {
	            double a=sqrt(dis2+x2+y*y);
	            sum+=1/(a*a*a)*d2;
	        }
	    }
        e=clock();
		double duration=(double)(e-s)/CLOCKS_PER_SEC;
	    cout<<"outcome: "<<sqrt(dis2)*6*sum*q/(4*pi)*4<<"/8.85^-12"<<endl<<"time: "<<duration<<"s\n\n";
	}
	return 0;
}
