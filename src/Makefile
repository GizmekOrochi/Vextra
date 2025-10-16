SRC = $(shell find core -name '*.cpp') main.cpp
CXX = g++
CXXFLAGS = -std=c++20 -Iinclude -Wall -Wextra
OUT = ../bin/vextra

com:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(OUT)

run:
	$(OUT)
