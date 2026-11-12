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
	
	cout<<endl<<"\nFinal Approximated Solution:\n";
	for(int i=0;i<n;i++)
	{
		cout<<setw(10)<<x[i];
	}
	cout<<endl<<"\nThe Residual Vector(r):\n";
	vector<double> r(n);
	for(int i=0;i<n;i++)
	{
		double r_i=b[i];
		for(int j=0;j<n;j++)
		{
			r_i-=(A[i][j]*x[j]);
		}
		cout<<setw(11)<<r_i;
		r[i]=r_i;
	}
	
	cout<<endl<<"\nEuclidean Norm of the rsidual ||r|| = ";
	double ans=0;
	for(int i=0;i<n;i++)
	{
		ans+=(r[i]*r[i]);
	}
	cout<<sqrt(ans)<<endl;
		
}

void SDD(vector<vector<double>>& A,int n)
{
	bool result=true;
	for(int i=0;i<n;i++)
	{
		double sum=0;
		for(int j=0;j<n;j++)
		{
			if(i!=j)sum+=fabs(A[i][j]);
		}
		if(fabs(A[i][i])<sum)
		{
			result=false;
			cout<<"\The matrix A does not satisfy the Strictly Diagonally Dominant condition\n";
			return;
		}
	}
	if(result)
	{
		cout<<"\The matrix A satisfies the Strictly Diagonally Dominant condition\n";
	}
}


int main()
{
	int n=8;
	vector<vector<double>> A = {
    {15.2, -2.1,  0.5,  1.1, -0.3,  2.0,  0.0, -1.5},
    {-1.0, 18.5, -3.2,  0.0,  2.5, -1.1,  0.8,  0.5},
    { 0.5, -2.0, 14.8, -4.1,  1.2,  0.0, -0.9,  2.1},
    { 1.1,  0.0, -3.0, 16.4, -2.2,  1.5, -0.5,  0.8},
    {-0.4,  2.2,  1.0, -2.5, 19.1, -3.0,  1.1,  0.0},
    { 2.1, -1.0,  0.0,  1.2, -2.8, 17.5, -3.5,  1.0},
    { 0.0,  0.9, -1.1, -0.5,  1.5, -3.2, 16.8, -2.2},
    {-1.2,  0.5,  2.0,  0.7,  0.0,  1.1, -2.5, 15.6}};
	
	vector<double> b = {
    14.9,
    -22.3,
    35.6,
    -11.2,
    42.8,
    -5.4,
    19.1,
    -28.4};
    
	double error;
	cout<<"\nEnter the required relative error range: ";
	cin>>error;
	
	vector<double> x(n);
	cout<<"\nEnter the intial approximation:\n";
	for(int i=0;i<n;i++)
	{
		cin>>x[i];
	}
	SDD(A,n);
	gaussSeidal(A,b,x,n,error);
	return 0;
}
