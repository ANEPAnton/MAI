all: image 

image: image.o main.o
	g++ *.o -o image

image.o:
	g++ -c image.cpp

main.o:
	g++ -c main.cpp
	
clean:
	rm -rf *.o image
