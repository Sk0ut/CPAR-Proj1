CXX=g++
RM=rm -f

all: matrixprod matrixtest

matrixprod:
	$(CXX) matrixprod.cpp utils.cpp matrixopr.cpp -O2 -fopenmp -lpapi -o matrixprod

matrixtest:
	$(CXX) matrixprodTests.cpp utils.cpp matrixopr.cpp -O2 -fopenmp -lpapi -o matrixtest

clean:
	$(RM) matrixprod
	$(RM) matrixtest
