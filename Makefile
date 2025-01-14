all: compile clean

compile:
	g++ mainTesting.cpp BMP.cpp -o prog
	./prog

clean:
	del *.o