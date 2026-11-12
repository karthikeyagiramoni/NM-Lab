#include<bits/stdc++.h>
using namespace std;

double equation(double x)
{
	return pow(x,3)+4*pow(x,2)-10;
}

double computeC(double a,double b)
{
	double A=equation(a);
	double B=equation(b);
	return (a*B-b*A)/(B-A);
}

void bisection(double a,double b,double ran,vector<vector<double>>& result)
{
	cout<<endl<<"BISECTION METHOD: "<<endl;
	if(equation(a)==0)
	{
		cout<<"The root="<<a;
		return;
	}
	if(equation(b)==0)
	{
		cout<<"The root="<<b;
		return;
	}
	if(equation(a)*equation(b)>0)
	{
		cout<<"Change the interval!";
		return;
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
			return;
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
	cout<<"\nApproximated Root="<<approx<<endl<<endl;
	result.push_back({1,approx,count-1,abs(equation(approx))});
}

void regulaFalsi(double a,double b,double ran,vector<vector<double>>& result)
{
	cout<<endl<<"REGULA FALSI METHOD:"<<endl;
	if(equation(a)==0)
	{
		cout<<"The root="<<a;
		return;
	}
	if(equation(b)==0)
	{
		cout<<"The root="<<b;
		return;
	}
	if(equation(a)*equation(b)>0)
	{
		cout<<"Change the interval!";
		return;
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
			result.push_back({2,c,count-1,0});
			return;
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
	cout<<"\nApproximated Root = "<<approx<<endl<<endl;
	result.push_back({2,approx,count-1,abs(equation(approx))});
}

int main()
{
	double a,b;
	cout<<"Enter the interval [a,b]: "<<endl;
	cin>>a>>b;
	double ran;
	cout<<"Enter the desired accuracy: ";
	cin>>ran;
	
	vector<vector<double>> result;
	
	bisection(a,b,ran,result);
	regulaFalsi(a,b,ran,result);
	
	for(int i=0;i<50;i++)
	{
		cout<<"-";
	}
	cout<<endl<<setw(11)<<"Method"<<setw(15)<<"Approx Root"<<setw(5)<<"Iter"<<setw(15)<<"f(root)"<<endl;
	for(int i=0;i<50;i++)
	{
		cout<<"-";
	}
	cout<<endl;
	cout<<setw(11)<<"Bisection"<<setw(15)<<result[0][1]<<setw(5)<<result[0][2]<<setw(15)<<result[0][3]<<endl;
	cout<<setw(11)<<"Regula Falsi"<<setw(15)<<result[1][1]<<setw(5)<<result[1][2]<<setw(15)<<result[1][3]<<endl;
}
