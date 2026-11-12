#include<bits/stdc++.h>
using namespace std;

double equation(double x)
{
	return exp(-x)-x;
}

double computeC(double a,double b)
{
	double A=equation(a);
	double B=equation(b);
	return (a*B-b*A)/(B-A);
}

int main()
{
	double a,b;
	cout<<"Enter the interval [a,b]: "<<endl;
	cin>>a>>b;
	double ran;
	cout<<"Enter the desired accuracy: ";
	cin>>ran;
	
	if(equation(a)==0)
	{
		cout<<"The root="<<a;
		return 1;
	}
	if(equation(b)==0)
	{
		cout<<"The root="<<b;
		return 1;
	}
	if(equation(a)*equation(b)>0)
	{
		cout<<"Change the interval!";
		return 0;
	}
	for(int i=0;i<68;i++)
	{
			cout<<"-";
	}
	cout<<endl<<setw(5)<<"Iter"<<setw(11)<<"a "<<setw(11)<<"b "<<setw(11)<<"c "<<setw(15)<<"f(c) "<<setw(15)<<"|b-a| "<<endl;
	for(int i=0;i<68;i++)
	{
			cout<<"-";
	}
	cout<<endl;
	double count=1;
	double approx;
	while((b-a)>ran)
	{
		double c=computeC(a,b);
		double C=equation(c);
		cout<<setw(5)<<count++<<setw(11)<<a<<setw(11)<<b<<setw(11)<<c<<setw(15)<<C<<setw(15)<<b-a<<endl;
		if(C==0)
		{
			cout<<"\nThe root="<<c<<endl;
			return 1;
		}
		if(equation(a)*C<0)
		{
			b=c;
		}
		else
		{
			a=c;
		}
		approx=c;
	}
	cout<<"\nNumber of Iterations="<<count-1<<endl;
	cout<<"\nApproximated Root = "<<approx<<endl;
	
	
}


