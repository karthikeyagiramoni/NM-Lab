#include<bits/stdc++.h>
#include<cmath>
using namespace std;

double f(double x,double y)
{
	return x*x+y*y-4;
}

double g(double x,double y)
{
	return exp(x)+y-1;
}

double fx(double x,double y)
{
	return 2*x;
}

double fy(double x,double y)
{
	return 2*y;
}

double gx(double x,double y)
{
	return exp(x);
}

double gy(double x,double y)
{
	return 1;
}

double newtonRaphson(double x,double y,double err)
{
	cout<<endl<<setw(5)<<"Iter"<<setw(11)<<"x"<<setw(11)<<"y"<<setw(15)<<"Delta x"<<setw(15)<<"Delta y"<<endl;
	double d_x=0,d_y=0;
	int count=1;
	do
	{
		if(f(x,y)==0.0 && g(x,y)==0.0)
		{
			cout<<"\nThe root is ("<<x<<","<<y<<")\n";
			return count-1;
		}
		double J=fx(x,y)*gy(x,y)-gx(x,y)*fy(x,y);
		double D1=f(x,y)*gy(x,y)-g(x,y)*fy(x,y);
		double D2=fx(x,y)*g(x,y)-gx(x,y)*f(x,y);
		d_x=-D1/J;
		d_y=-D2/J;
		cout<<setw(5)<<count++<<setw(11)<<x<<setw(11)<<y<<setw(15)<<d_x<<setw(15)<<d_y<<endl;
		x+=d_x;
		y+=d_y;
	}
	while(max(abs(d_x),abs(d_y))>=err);
	cout<<"\nThe Approximated Root = ("<<x<<","<<y<<")\n";
	return count-1;
}

int main()
{
	double x,y;
	cout<<"\nEnter the initial approximation of (x,y): \n";
	cin>>x>>y;
	double err;
	cout<<"\nEnter the required range of error: ";
	cin>>err;
	
	double iter=newtonRaphson(x,y,err);
	cout<<"\nNumber of iterations required = "<<iter<<endl;
}
