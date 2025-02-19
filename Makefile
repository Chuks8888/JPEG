all: compile clean

compile:
	g++ mainTesting.cpp BMP.cpp dct.cpp -lm -o prog
	./prog

clean: