check: *.cpp *.hpp
	${CXX} -std=c++17 -o $@ *.cpp -O3 -fno-exceptions -fno-rtti
