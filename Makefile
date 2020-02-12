check: *.cpp *.hpp
	${CXX} -std=c++17 -o $@ *.cpp -g0 -O3 -fno-exceptions -fno-rtti -isystem gsl/include
