#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int Mx,My,MinX,MinY,MaxX,MaxY;
int Mass[500][500];
int SMass[500][500];
char ch[500][500];
FILE *massive;

void GetValues() {
	int h;
	h=1;
	while (fgets(ch[h], 500, massive)) { // берёт 500 символов из файла и заталкивает в переменную ch. Он не берёт одни и теже символы
		h++;//заменяет h=1 на h=2 и т.д, когда заканчиваются символы, while заканчивается.
	}
}

void Convert() {
	int x,d,y;
	d=1;
	char *buf;
	buf=strtok(ch[1], " \n");//strtok разбивает координаты на два числа
	while (buf!=NULL){//буфер
		if (d==1){Mx=atoi(buf); d++;}//atoi переводит char в int
		else {My=atoi(buf); d=1;}// повторный заход
		buf=strtok(NULL, " \n");// ch1 задаёт рамки массива(максимальные значения массива, длина и высота картинки)
	}
	buf=strtok(ch[2], " \n");
	while (buf!=NULL){
		if (d==1){x=atoi(buf); d++;}
		else {y=atoi(buf); Mass[x][y]=1; d=1;}
		buf=strtok(NULL, " \n");// ch2 хранит все координаты точек в массиве
	}
}

void Sort() { //Sort проверяет наличие точек рядом с другими точками
	int i,j,a;
	for(j=1;j<My;j++) { // По строкам
		for(i=1;i<Mx;i++) { // По столбцам
			// вокруг одной точки проверяем 8 точек
			if (Mass[i+1][j-1]==1) a++;
			if (Mass[i+1][j]==1) a++;
			if (Mass[i+1][j+1]==1) a++;
			if (Mass[i][j-1]==1) a++;
			if (Mass[i][j+1]==1) a++;
			if (Mass[i-1][j-1]==1) a++;
			if (Mass[i-1][j]==1) a++;
			if (Mass[i-1][j+1]==1) a++;
			//Проверка:
			if (a>=2) SMass[i][j] = Mass[i][j];//SMass - массив из нужных точек, Mass - массив всех точек
			if (SMass[i][j]==1) {
                // Далее задаются переменные для описания границ рамки нужных точек
				if (i>MaxX) MaxX=i;//максимальные точки рамки
				if (j>MaxY) MaxY=j;
				if (MinX==0) MinX=i;//минимальные точки
				if (MinY==0) MinY=j;
				}
			a=0;//сбрасывает значение а, чтобы мы могли определять следующую точку
		}
	}
}

void Contour() {//рисует на сетке квадратик вокруг точек(рамку)
	int i;
	for(i=MinX-1;i<=MaxX+1;i++) {//строит стороны по x
		SMass[i][MinY-1]=4;
		SMass[i][MaxY+1]=4;
	}
	for(i=MinY-1;i<=MaxY+1;i++) {//строит стороны по y
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
	printf("\nPloshad' s iskomimi to4kami =");
	printf("\nMx=%d\nMy=%d\n",MaxX-MinX+1,MaxY-MinY+1);
}

void Image() {//всё для вывода картинки
	int i,j;
	printf("P3\n");//цветная картинка
	printf("%d %d\n",Mx,My);//размеры
	printf("255\n");//максимальное значение оттенков
	for(j=0;j<My;j++) {
		for(i=0;i<Mx;i++) {
			if (SMass[i][j]==1) printf("0 0 0 ");
			else if (SMass[i][j]==2) printf("255 0 0 ");
			else if (SMass[i][j]==3) printf("0 255 0 ");
			else printf("255 255 255 ");
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {//argv - сами аргументы, argv 0 - прога(gcc), argv 1 - путь к файлику, argv 2 - единичка
	if (argc>3) {  //argc(счётчик) количество аргументов,1 аргумент - прога, 2 аргумента - прога+путь к файлу, 3 - прога+путь к файлу+ символ(единичка в codeblocks)
		printf("Slishkom mnogo argumentov!\n");//Слишком много аргументов
		exit(0);
	}
	massive=fopen(argv[1], "r");// путь к файлику, fopen открывает файл по пути с разрешением только для чтения "r" и переменная File хранит путь к себе
	if (massive==NULL) { // будет NULL если не открыл
		printf("Oshibka otkritiya izobrajenia\n"); //Не удалось открыть изображение
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

