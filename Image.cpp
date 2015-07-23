#include "image.h"


using namespace std;

	image::image(int x, int y)
	{
		this->img = new int*[x];
		for(int i=0;i<x;i++)
		{
			this->img[i]=new int[y];
				for (int j=0;j<y;j++)
					this->img[i][j]=0;
		}
		this->x=x;
		this->y=y;
		
	}

	int image::getx()
	{
		return this->x;
	}

	int image::gety()
	{
		return this->y;
	}

	int image::getb(int x,int y)
	{
		return this->img[x][y];
	}

	void image::printimage()
	{
		for(int i=0; i<this->x;i++)
		{
			for(int j=0;j<this->y;j++)
				cout<<this->img[i][j]<<" ";
			cout<<endl;
		}

	}

	void image::setpoint(vector <int*> points)
	{
		for(int i=0; i<points.size();i++)
		{
			this->img[points[i][0]][points[i][1]]=1;
		}
	}

	void image::showrad(int r, int *a){
		int xc,xf,yc,yf;

		if(a[0]-r<0)
			xc=0;
		else 
			xc=a[0]-r;
//
		if(a[1]-r<0)
			yc=0;
		else 
			yc=a[1]-r;
//
		if(a[0]+r>=this->getx())
			xf=this->getx();
		else 
			xf=t[0]+r;
//
		if(a[1]+r>=this->gety())
			yf=this->gety();
		else 
			yf=a[1]+r;		
//
		for(int i=xc;i<xf;i++)
			for(int j=yc;j<yf;j++)
			{
				if(this->img[i][j]==0)
				{
				
				if((i==xc)||(i==xf-1))
					this->img[i][j]=3;	

				if((j==yc)||(j==yf-1))
					this->img[i][j]=3;

				}
			}
			

		this->img[a[0]][a[1]]=2;

	}

	int image::radprov(int x1, int y1, int x2, int y2,int r)
	{
		double r1=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
		if(r1>(double)r) return 0;
		return 1;
	}

	int image::prov(vector<int*> b, int*a)
	{

		for(int i=0;i<b.size();i++)
			if((a[0]==b[i][0])&&(a[1]==b[i][1]))
				return 0;

		return 1;
	}

	vector<int*> image::getobject(int r,int fl)
	{
		vector<int*> b;
		vector<int*> b1;
		int *d=new int[2];
		int *a;
		
		for(int i=0;i<this->x;i++)
		{
			for(int j=0;j<this->y;j++)
			{
				b1.clear();
				for(int i1=0;i1<=r;i1++)
					for(int j1=0;j1<=r;j1++)
					{
						if((j-j1>=0)&&(i-i1>=0))
						{
							if((this->radprov(j,i,j-j1,i-i1,r))&&(this->img[i-i1][j-j1]==1))
							{
								a=new int[2];
								a[1]=j-j1;
								a[0]=i-i1;
								if(prov(b1,a))
								b1.push_back(a);
							}
						}

						if((j+j1<this->y)&&(i+i1<this->x))
						{
							if((this->radprov(j,i,j+j1,i+i1,r))&&(this->img[i+i1][j+j1]==1))
							{
								a=new int[2];
								a[1]=j+j1;
								a[0]=i+i1;
								if(prov(b1,a))
									b1.push_back(t);
							}
						}
						
					}

				if(b1.size()>b.size()){
					b=b1;
					d[1]=j;
					d[0]=i;
				}
			}
		}
		if(fl!=0)
		{
			b.clear();
			b.push_back(d);
		}
		else cout<<"Центр области: "<<endl<<"x= "<<d[0]<<"y= "<<d[1]<<endl;
		return b;
	}

