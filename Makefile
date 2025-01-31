all: compile clean

compile:
	g++ mainTesting.cpp BMP.cpp -lm -o prog
	./prog

clean: