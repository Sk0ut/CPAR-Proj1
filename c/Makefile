CXX=g++
RM=rm -f

all: matrixprod

matrixprod:
	$(CXX) matrixprod.cpp utils.cpp matrixopr.cpp -O2 -fopenmp -lpapi -o matrixprod

clean:
	$(RM) matrixprod
