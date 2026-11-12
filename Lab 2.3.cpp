#include<bits/stdc++.h>
#include<cmath>
using namespace std;

double f(double x)
{
	return 2*x-3-cos(x);
}

double phi(double x)
{
	return (cos(x)+3)/2;
}

int fixedPoint(double x,double err)
{
	if(x==phi(x))
	{
		cout<<"\nThe root is "<<x<<endl;
		return 0;
	}
	int count=1;
	cout<<endl<<setw(5)<<"Iter"<<setw(11)<<"x_n"<<setw(15)<<"phi(x_n)"<<setw(15)<<"f(x_n)"<<setw(15)<<"Error"<<endl;
	double temp;
	do
	{
		if(x==phi(x))
		{
			cout<<"\nThe root is "<<x<<endl;
			return count-1;
		}
		double p=phi(x);
		temp=abs(p-x);
		cout<<setw(5)<<count++<<setw(11)<<x<<setw(15)<<p<<setw(15)<<f(x)<<setw(15)<<temp<<endl;
		x=p;
	}
	while(temp>=err);
	cout<<"\nThe Approximated Root = "<<x<<endl;
	return count-1;
}

int aitken(double x,double err)
{
	if(f(x)==0)
	{
		cout<<"\nThe root is "<<x<<endl;
		return 0;
	}
	
	int count=1;
	cout<<endl<<setw(5)<<"Iter"<<setw(11)<<"x_n"<<setw(15)<<"phi(x_n)"<<setw(15)<<"f(x_n)"<<setw(15)<<"Error"<<endl;
	double temp;
	double x0=x;
	double x1=phi(x);
	count=1;
	temp=abs(x1-x0);
	cout<<setw(5)<<count++<<setw(11)<<x0<<setw(15)<<x1<<setw(15)<<f(x0)<<setw(15)<<temp<<endl;
	double x2=phi(x1);
	temp=abs(x2-x1);
	cout<<setw(5)<<count++<<setw(11)<<x0<<setw(15)<<x1<<setw(15)<<f(x0)<<setw(15)<<temp<<endl;
	do
	{
		if(f(x2)==0)
		{
			cout<<"\nThe root is "<<x<<endl;
			return 0;
		}
		double d_x1=x2-x1;
		double d2_x0=x2-2*x1+x0;
		double x3=x2-(d_x1*d_x1)/d2_x0;
		temp=abs(x3-x2);
		cout<<setw(5)<<count++<<setw(11)<<x2<<setw(15)<<x3<<setw(15)<<f(x2)<<setw(15)<<temp<<endl;
		x0=x1;
		x1=x2;
		x2=x3;
	}
	while(temp>=err);
	cout<<"\nThe Approximated Root = "<<x2<<endl;
	return count-1;
}

int main()
{
	double x;
	cout<<"Enter a suitable initial approximation in [3/2,pi/2]: ";
	cin>>x;
	double err;
	cout<<"Enter the required range of error: ";
	cin>>err;
	
	cout<<"\nFIXED POINT METHOD\n";
	int iter1=fixedPoint(x,err);
	cout<<"\nNumber of iterations required = "<<iter1<<endl;
	cout<<"\nAITKEN'S MODIFICATION\n";
	int iter2=aitken(x,err);
	cout<<"\nNumber of iterations required = "<<iter2<<endl;
	
}
