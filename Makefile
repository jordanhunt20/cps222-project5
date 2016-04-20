# Makefile for CPS222 Project 5
# Makes file project5

project5:	Graph.o project5.o
	g++ -o $@ $^

Graph.o:	Graph.h
project4.o:	Graph.h

%.o:	%.cc
	g++ -c $<
