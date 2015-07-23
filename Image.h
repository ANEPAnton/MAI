#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <math.h>
#include <vector>


using namespace std;
	class image
	{
		private:
			int x,y;
			int **img;
		public:
			image(int x, int y);
			int getx();
			int gety();
			int getp(int x,int y);
		void printimage();
		void showrad(int r, int *t);
		void setpoint(vector <int*> points);
		int radprov(int x1, int y1, int x2, int y2,int r);
		int prov(vector<int*> p, int*t);

		vector<int*> getobject(int r,int fl);

	};



#endif
