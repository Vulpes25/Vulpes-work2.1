#include <iostream>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

#define N 201;
#define LB 0.5;
#define RB -0.5;
#define dx 0.01;
#define dt 0.02*dx;

int main()
{
	//1. 设置初始条件
	double U;
	double T;

	cout<<"请输入μ的值"<<endl;
	cin >> U;
	cout<<"请输入时间"<<endl;
	cin>>T;

	double u[201];
	double u_p[201];
	double x[201];
	double ct=0.0;
	double u_t=1;
	double u2_t2=1;
	double u_x=1;
	double u2_x2=1;


	//2.确定初值


	//2.1 插值初值中间值
	//2.2 初值边界

	
	for(int i=1;i<200;i++)
	{
		x[i]=-1.0+i/100.0;
	}

	x[0]=-1;
	x[200]=1;

	for(int i=1;i<200;i++)
	{
		u[i]=-0.5*x[i];
	}
	u[0]=0.5;
	u[200]=-0.5;
	for(int j=0;ct<T;j++)
	{
		ct=ct+0.0002;

		//3. 计算

		for(int i=0;i<201;i++)
		{
			u_p[i]=u[i];
		}
		
		for(int i=1;i<200;i++)
		{
			//3.1 计算u_x和u2_x2

			if(u_p[i]>=0)
			{
				if(i>1)
				{
					u_x=(3.0*u_p[i]-4.0*u_p[i-1]+u_p[i-2])/(0.01*2.0);
				}
				else
				{
					u_x=(3.0*u_p[i]-4.0*u_p[i-1]+u_p[0])/(0.01*2.0);
				}
			}
			else
			{
				if(i<199)
				{
					u_x=(-3.0*u_p[i]+4.0*u_p[i+1]-u_p[i+2])/(0.01*2.0);
				}
				else
				{
					u_x=(-3.0*u_p[i]+4.0*u_p[i+1]-u_p[200])/(0.01*2.0);
				}
			}

			u2_x2=(u_p[i+1]-2.0*u_p[i]+u_p[i-1])/(0.01*0.01);

			//3.2 计算u_t,u2_t2

			u_t=-u_p[i]*u_x+U*u2_x2;
			u2_t2=-3.0*U*u_x*u2_x2-u_t*u_x+u_p[i]*u_p[i]*u2_x2+u_p[i]*u_x*u_x;

			//3.3计算u

			u[i]=u_p[i]+0.0002*u_t+pow(0.0002,2)*u2_t2/2.0;
		}
	}


	ofstream file;
	file.open("0420.dat");
	file << "variables = x,u" << endl;
	file << "zone t = naca, i = " << 201  << endl;   
	for(int i=0;i<201;i++)       
	{          
		file << x[i] << " " <<  u[i]<<endl;     
	}    

	cout<<u[10]<<" "<<u_p[10]<<" "<<u_x<<" "<<u2_x2<<" "<<u_t<<" "<<u2_t2<<endl;

	system ("pause");
	return 0;
}