#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Mx,My,MinX,MinY,MaxX,MaxY;
int Mass[500][500];
int SMass[500][500];
char ch[500][500];
FILE *massive;

void GetValues() {
	int h;
	h=1;
	while (fgets(ch[h], 500, massive)) {
		h++;
	}
}

void Convert() {
	int x,d,y;
	d=1;
	char *buf;
	buf=strtok(ch[1], " \n");
	while (buf!=NULL){
		if (d==1){Mx=atoi(buf); d++;}
		else {My=atoi(buf); d=1;}
		buf=strtok(NULL, " \n");
	}
	buf=strtok(ch[2], " \n");
	while (buf!=NULL){
		if (d==1){x=atoi(buf); d++;}
		else {y=atoi(buf); Mass[x][y]=1; d=1;}
		buf=strtok(NULL, " \n");
	}
}

void Sort() {
	int i,j,a;
	for(j=1;j<My;j++) {
		for(i=1;i<Mx;i++) {

			if (Mass[i+1][j-1]==1) a++;
			if (Mass[i+1][j]==1) a++;
			if (Mass[i+1][j+1]==1) a++;
			if (Mass[i][j-1]==1) a++;
			if (Mass[i][j+1]==1) a++;
			if (Mass[i-1][j-1]==1) a++;
			if (Mass[i-1][j]==1) a++;
			if (Mass[i-1][j+1]==1) a++;

			if (a>=2) SMass[i][j] = Mass[i][j];
			if (SMass[i][j]==1) {
				if (i>MaxX) MaxX=i;
				if (j>MaxY) MaxY=j;
				if (MinX==0 || i<MinX) MinX=i;
                if (MinY==0 || i<MinY) MinY=j;
				}
			a=0;
		}
	}
}

void Contour() {
	int i;
	for(i=MinX-1;i<=MaxX+1;i++) {
		SMass[i][MinY-1]=4;
		SMass[i][MaxY+1]=4;
	}
	for(i=MinY-1;i<=MaxY+1;i++) {
		SMass[MinX-1][i]=3;
		SMass[MaxX+1][i]=3;
	}
}

void CenterOfMass() {
	int i,j;
	j=(MaxY+MinY)/2;
	i=(MaxX+MinX)/2;
	SMass[i][j]=2;
}

void Print() {
	int i,j;
	printf("\nPloshad' s iskomimi to4kami: X=%d, Y=%d\n\n",MaxX-MinX+1,MaxY-MinY+1);

	for(j=0;j<My;j++) {
		for(i=0;i<Mx;i++) {
			if (SMass[i][j]==1) printf("O");
			else if (SMass[i][j]==2) printf("*");
			else if (SMass[i][j]==3) printf("|");
			else if (SMass[i][j]==4) printf("-");
			else printf(".");
		}
		printf("\n");
	}

}

void Image() {
	int i,j;
	printf("P3\n");
	printf("%d %d\n",Mx,My);
	printf("255\n");
	for(j=0;j<My;j++) {
		for(i=0;i<Mx;i++) {
			if (SMass[i][j]==1) printf("0 0 0 ");
			else if (SMass[i][j]==2) printf("255 0 0 ");
			else if (SMass[i][j]==3) printf("255 255 0 ");
			else if (SMass[i][j]==4) printf("255 255 0 ");
			else printf("255 255 255 ");
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	if (argc>3) {
		printf("Slishkom mnogo argumentov!\n");
		exit(0);
	}
	massive=fopen(argv[1], "r");
	if (massive==NULL) {
		printf("Oshibka otkritiya izobrajenia\n");
		exit(1);
	}
	GetValues();
	Convert();
	Sort();
	Contour();
	CenterOfMass();
	if (argc==3)
	Print();
	if (argc==2)
	Image();
}
