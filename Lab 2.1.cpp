#include<bits/stdc++.h>
#include<cmath>
using namespace std;

double equation(double x)
{
	return x-cos(x);
}

double derEquation(double x)
{
	return 1+sin(x);
}

int newtonRaphson(double x,double err)
{
	if(equation(x)==0.0)
	{
		cout<<"The root is "<<x<<endl;
	}
	cout<<endl<<setw(5)<<"Iter"<<setw(11)<<"Xn"<<setw(15)<<"f(Xn)"<<setw(15)<<"f'(Xn)"<<setw(11)<<"Xn+1"<<endl;
	double y=x;
	int count=1;
	do
	{
		if(equation(y)==0.0)
		{
			cout<<"\nThe root is "<<y<<endl;
			return count-1;
		}
		x=y;
		double f=equation(x);
		double f_d=derEquation(x);
		y=x-f/f_d;
		cout<<setw(5)<<count++<<setw(11)<<x<<setw(15)<<f<<setw(15)<<f_d<<setw(11)<<y<<endl;
	}
	while(abs(y-x)>=err);
	cout<<"\nThe Approximated Root = "<<y<<endl;
	return count-1;
}

int main()
{
	double x,err;
	cout<<"Enter the initial approximation: ";
	cin>>x;
	cout<<"Enter the required range of error: ";
	cin>>err;
	int iter=newtonRaphson(x,err);
	cout<<"\nNumber of iterations required = "<<iter<<endl;
}
