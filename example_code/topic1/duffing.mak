# makefile to compile lecture 1 codes

all : duffing.exe duffing_f90.exe ;

duffing.exe : duffing.cpp
	c++ -o duffing.exe duffing.cpp

duffing_f90.exe : duffing.f90
	gfortran -o duffing_f90.exe duffing.f90
