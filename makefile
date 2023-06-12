CC=mpicxx

all: clean main.exe


main.exe:
	$(CC) -std=c++14 main.cpp src/*.cpp -o main.exe


.PHONY: clean all
clean:
	rm -rf main.exe main.dsym
