#include<bits/stdc++.h>
using namespace std;

void gaussSeidal(vector<vector<double>>& A,vector<double>& b,vector<double>& x,int n,double error)
{
	cout<<"\nGAUSS-SEIDAL METHOD:"<<endl;
	cout<<endl<<setw(5)<<"Iter";
	for(int i=0;i<n;i++)
	{
		cout<<setw(10)<<("x"+to_string(i+1)+" ");
	}
	for(int i=0;i<n;i++)
	{
		cout << setw(15) << ("Err(x" + to_string(i + 1) + ") ");
	}
	cout<<endl;
	int count=0;
	vector<double> err(n,0.0);
	vector<double> Oldx=x;
	double maxErr;
	while(count<100)
	{
		maxErr=0.0;
		Oldx=x;
		for(int i=0;i<n;i++)
		{
			double x_n=b[i];
			for(int j=0;j<n;j++)
			{
				if(i!=j)
				{
					x_n-=(A[i][j]*x[j]);
				}
			}
			x[i]=x_n/A[i][i];
		}
		for(int i=0;i<n;i++)
		{
			if(x[i]!=0.0)
			{
				err[i]=fabs((x[i]-Oldx[i])/x[i]);
			}
			else
			{
				err[i]=fabs(x[i]-Oldx[i]);
			}
			maxErr=max(maxErr,err[i]);
		}
		cout<<setw(5)<<++count;
		for(int i=0;i<n;i++)
		{
			cout<<setw(10)<<x[i];
		}
		for(int i=0;i<n;i++)
		{
			cout<<fixed<<setprecision(6);
			cout<<setw(15)<<err[i];
		}
		cout<<endl;
		if(maxErr<error)break;
	}
	cout<<"\nTotal number of iterations required = "<<count<<endl;
	
	cout<<"\nThe Residual Vector:\n";
	for(int i=0;i<n;i++)
	{
		double r=b[i];
		for(int j=0;j<n;j++)
		{
			r-=(A[i][j]*x[j]);
		}
		cout<<setw(11)<<r;
	}
}


int main()
{
	int n;
	cout<<"Enter the number of variables: ";
	cin>>n;
	vector<vector<double>> A(n);
	cout<<"\nEnter the matrix A:\n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			double temp;
			cin>>temp;
			A[i].push_back(temp);
		}
	}
	vector<double> b(n);
	cout<<"\nEnter the vector b:\n";
	for(int i=0;i<n;i++)
	{
		cin>>b[i];
	}
	double error;
	cout<<"\nEnter the required relative error range: ";
	cin>>error;
	
	vector<double> x(n);
	cout<<"\nEnter the intial approximation:\n";
	for(int i=0;i<n;i++)
	{
		cin>>x[i];
	}
	
	gaussSeidal(A,b,x,n,error);
	return 0;
}
