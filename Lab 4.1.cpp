#include<bits/stdc++.h>
using namespace std;

void gaussJacobi(vector<vector<double>>& A,vector<double>& b,vector<double> x,int n,double tolerance,vector<double>& ans1,int& f1,int& iter1)
{
	cout<<"\nGAUSS-JACOBI METHOD:\n";
	cout<<endl<<setw(5)<<"Iter";
	for(int i=0;i<n;i++)
	{
		cout<<setw(10)<<("x"+to_string(i+1)+" ");
	}
	
	cout<<setw(15)<<"Error"<<endl;
	double olderr=0;
	double f_error=0;
	vector<double> oldx=x;
	bool f=false;
	int count=0;
	do
	{
		if(olderr<f_error)f=true;
		olderr=f_error;
		oldx=x;
		double error=0;
		vector<double> err(n);
		for(int i=0;i<n;i++)
		{
			double temp=b[i];
			for(int j=0;j<n;j++)
			{
				if(i!=j)
				{
					temp-=(A[i][j]*oldx[j]);
				}
			}
			temp/=A[i][i];
			x[i]=temp;
			err[i]=abs(oldx[i]-x[i]);
			if(error<err[i])error=err[i];
		}
		f_error=error;
		cout<<setw(5)<<++count;
		for(int i=0;i<n;i++)
		{
			cout<<setw(10)<<x[i];
		}
		cout<<setw(15)<<f_error<<endl;
	}
	while(f_error>=tolerance && count<30);
	if(f)
	{
		f1=1;
		cout<<"\nStatus: Diverging\n";
	}
	else
	{
		f1=0;
		cout<<"\nStatus: Converging\n";
	}
	cout<<"\nTotal number of iterations= "<<count<<endl;
	iter1=count;
	cout<<"\nThe final solution:\n";
	for(int i=0;i<n;i++)
	{
		ans1[i]=x[i];
		cout<<setw(10)<<x[i];
	}
	cout<<endl<<endl;
}

void gaussSeidal(vector<vector<double>>& A,vector<double>& b,vector<double>& x,int n,double tolerance,vector<double>& ans2,int& f2,int& iter2)
{
	cout<<"\nGAUSS-SEIDAL METHOD:\n";
	cout<<endl<<setw(5)<<"Iter";
	for(int i=0;i<n;i++)
	{
		cout<<setw(10)<<("x"+to_string(i+1)+" ");
	}
	
	cout<<setw(15)<<"Error"<<endl;
	double olderr=0;
	double f_error=0;
	vector<double> oldx=x;
	bool f=false;
	int count=0;
	do
	{
		if(olderr<f_error)f=true;
		else
		{
			f=false;
		}
		olderr=f_error;
		oldx=x;
		double error=0;
		vector<double> err(n);
		for(int i=0;i<n;i++)
		{
			double temp=b[i];
			for(int j=0;j<n;j++)
			{
				if(i!=j)
				{
					temp-=(A[i][j]*x[j]);
				}
			}
			temp/=A[i][i];
			x[i]=temp;
			err[i]=abs(oldx[i]-x[i]);
			if(error<err[i])error=err[i];
		}
		f_error=error;
		cout<<setw(5)<<++count;
		for(int i=0;i<n;i++)
		{
			cout<<setw(10)<<x[i];
		}
		cout<<setw(15)<<f_error<<endl;
	}
	while(f_error>=tolerance && count<30);
	if(f)
	{
		f2=1;
		cout<<"\nStatus: Diverging\n";
	}
	else
	{
		f2=0;
		cout<<"\nStatus: Converging\n";
	}
	cout<<"\nTotal number of iterations= "<<count<<endl;
	iter2=count;
	cout<<"\nThe final solution:\n";
	for(int i=0;i<n;i++)
	{
		ans2[i]=x[i];
		cout<<setw(10)<<x[i];
	}
	cout<<endl<<endl;
}

int main()
{
	int n=5;
	vector<vector<double>> A={
	{3,2,-2,-1,1},
	{0,4,1,-2,1},
	{2,-2,3,-2,2},
	{2,-2,2,4,-2},
	{-2,-1,0,0,3}};
	vector<double> b={4,-1,-15,12,-10};
	double error;
	cout<<"\nEnter the required relative error range: ";
	cin>>error;
	
	vector<double> x(n);
	cout<<"\nEnter the intial approximation:\n";
	for(int i=0;i<n;i++)
	{
		cin>>x[i];
	}
	vector<double> ans1(n);
	vector<double> ans2(n);
	int f1,f2;
	int iter1,iter2;
	
	gaussJacobi(A,b,x,n,error,ans1,f1,iter1);
	gaussSeidal(A,b,x,n,error,ans2,f2,iter2);
	
	cout<<"\n===COMPARISION TABLE===\n";
	cout<<setw(10)<<"METHOD"<<setw(15)<<"STATUS"<<setw(10)<<"ITER"<<setw(10)<<"X1"<<setw(10)<<"X2"<<setw(10)<<"X3"<<setw(10)<<"X4"<<setw(10)<<"X5"<<endl;
	cout<<setw(10)<<"Jacobi";
	if(f1==1)
	{
		cout<<setw(15)<<"Diverging";
	}
	else
	{
		cout<<setw(15)<<"Converging";
	}
	cout<<setw(10)<<iter1<<setw(10)<<ans1[0]<<setw(10)<<ans1[1]<<setw(10)<<ans1[2]<<setw(10)<<ans1[3]<<setw(10)<<ans1[4]<<endl;
	cout<<setw(10)<<"GaussSeidal";
	if(f2==1)
	{
		cout<<setw(15)<<"Diverging";
	}
	else
	{
		cout<<setw(15)<<"Converging";
	}
	cout<<setw(10)<<iter2<<setw(10)<<ans2[0]<<setw(10)<<ans2[1]<<setw(10)<<ans2[2]<<setw(10)<<ans2[3]<<setw(10)<<ans2[4]<<endl;
	return 0;
}
