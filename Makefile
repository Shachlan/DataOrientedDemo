check: *.cpp *.hpp
	${CXX} -std=c++17 -o $@ *.cpp -O0 -g  -isystem gsl/include

fastCheck: *.cpp *.hpp
	${CXX} -std=c++17 -o $@ *.cpp -O3 -g0 -fno-exceptions -fno-rtti -isystem gsl/include
