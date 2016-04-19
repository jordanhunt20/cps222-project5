# Makefile for CPS222 Project 5
# Makes file project5

project5: 	province.o town.o road.o project5.o
	g++ -o $@ $^

province.o:	province.h town.h road.h
town.o: town.h road.h
road.o:	road.h
project4.o:	province.h

%.o:	%.cc
	g++ -c $<
