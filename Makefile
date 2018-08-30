# Madeleine Schwartz
# July 8th
# Makefile for getGender program

C = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2
LDFLAGS = -g3

getGender: getGender.o main.o
	$(CXX) $(CXXFLAGS) -o getGender getGender.o main.o

getGender.o: getGender.cpp getGender.h
main.o: main.cpp

clean:
	rm -fg getGender *.o *.dSYM


