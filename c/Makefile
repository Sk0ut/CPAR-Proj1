CXX=g++
RM=rm -f

all: matrixprod

matrixprod:
	$(CXX) matrixprod.cpp -O2 -fopenmp -lpapi -o matrixprod

clean:
	$(RM) matrixprod
