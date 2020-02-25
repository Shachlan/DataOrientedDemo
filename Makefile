debug: *.cpp *.hpp
	${CXX} -std=c++17 -o check *.cpp -O0 -g  -isystem gsl/include

check: *.cpp *.hpp
	${CXX} -std=c++17 -o check *.cpp -O3 -g0 -fno-exceptions -fno-rtti -isystem gsl/include
