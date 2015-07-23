#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include "image.h"

using namespace std;

int centerofmass;
vector<int> pointreceive;
int sizereceive;
void imagereference;
void imageresearch


int main(int argc, char *argv[])
	{	
		
		int r=4; 
		int *c;

		vector<int*> b;
		b=pointreceive(argv[1]);
		c=sizereceive(b);
		image *img=new image(c[0]+1,c[1]+1);
		img->setpoints(b);
		cout<<"Значение радиуса"<<endl<<r<<endl;

		vector<int*> object;
		object=img->getobject(r,0);
		cout<<"Значение объекта:"<<endl;
				for(int i=0;i<object.size();i++)
			cout<<"		x= "<<object[i][0]<<" y= "<<object[i][1]<<endl;
		cout<<"Значение центра масс:"<<endl;
		c=centerofmass(object);
		cout<<"		x= "<<c[0]<<" y= "<<c[1]<<endl;
		
		imagereference(img);
		imageresearch(img,r);

			return 0;
	}
	
int* centerofmass(vector<int*> object)
  {
	int *a=new int[2];
	double x=0;
	double y=0;
		
		for(int i=0;i<object.size();i++)
		{
			x+=object[i][0];
			y+=object[i][1];
		}
	x=x/object.size();
	y=y/object.size();

	a[0]=(int)x;
	a[1]=(int)y;

	return a;
  }

vector<int*> pointreceive( char* filename){
	vector<int*> b;
	ifstream f(filename);
	int x,y;
	int *a;
	
	while (!f.eof()){
		f>>x>>y;
		a=new int[2];
		a[0]=x;
		a[1]=y;
		b.push_back(a);
	}
	
	return b;
};

int* sizereceive(vector <int*> b)
	{
		int *c=new int[2];
		c[0]=0;
		c[1]=0;

			for(int i=0; i<b.size();i++)
		{
			if(c[0]<b[i][0]) c[0]=b[i][0];
			if(c[1]<b[i][1]) c[1]=b[i][1];

		}

	return c;
	}

void imagereference(image* i1)
	{
		char fn[]="image.pnm";
		ofstream file(fn);
		file<<"P3"<<endl;
		file<<i1->gety()<<" "<<i1->getx()<<endl;
		file<<255<<endl;

			for(int i=i1->getx()-1; i>=0;i--)
			{
				for(int j=0;j<i1->gety();j++)
				{
					if(i1->getp(i,j)!=0)
						file<<"0 0 0"<<endl;
					else
						file<<"255 255 255"<<endl;
				}
			}
	file.close();
	}

void imageresearch(image* i1,int r)
	{
		char fn[]="object.pnm";
		ofstream file(fn);
		vector<int*> b;
		int *a;

		a=i1->getobject(r,1)[0];
		i1->drawrad(r,t);

		file<<"P3"<<endl;
		file<<i1->gety()<<" "<<i1->getx()<<endl;
		file<<255<<endl;

		for(int i=i1->getx()-1; i>=0;i--)
		{
			for(int j=0;j<i1->gety();j++)
			{
				switch(i1->getp(i,j))
				{
					case 0:file<<"255 255 255"<<endl;break;
					case 1: file<<"0 0 0"<<endl;break;
					case 2: file<<"100 200 0"<<endl;break;
					case 3: file<<"100 100 100"<<endl;break;
				}	
			}			
		}

		file.close();
	}
