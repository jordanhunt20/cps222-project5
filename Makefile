# Makefile for CPS222 Project 5
# Makes file project5

project5:	province.o project5.o
	g++ -o $@ $^

province.o:	province.h

%.o:	%.cc
	g++ -c $<
