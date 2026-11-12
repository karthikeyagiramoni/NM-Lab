#include<bits/stdc++.h>
using namespace std;

double equation(double x)
{
	return pow(x,3)-x-2;
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
	double count=1;
	double approx;
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
	while((b-a)>ran)
	{
		double c=(a+b)/2;
		double C=equation(c);
		cout<<setw(5)<<count++<<setw(11)<<a<<setw(11)<<b<<setw(11)<<c<<setw(15)<<C<<setw(15)<<b-a<<endl;
		
		if(C==0)
		{
			cout<<"The root="<<c;
			return 1;
		}
		if(C*equation(a)<0)
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
	cout<<"\nApproximated Root="<<approx<<endl;
	
}
