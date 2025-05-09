# makefile to compile lecture 2 codes

all : fpu.exe fpu_f90.exe ;

fpu.exe : fpu.cpp
	c++ -o fpu.exe fpu.cpp

fpu_f90.exe : fpu.f90
	gfortran -o fpu_f90.exe fpu.f90
