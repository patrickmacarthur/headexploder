# Makefile for HeaderExploder

CXX=g++
CXXFLAGS=-g -Wall

headexploder : explode.o HeaderExploder.o
	${CXX} ${CXXFLAGS} -o headexploder explode.o HeaderExploder.o

explode.o : explode.cc HeaderExploder.h
	${CXX} ${CXXFLAGS} -c -o explode.o explode.cc

HeaderExploder.o : HeaderExploder.cc HeaderExploder.h
	${CXX} ${CXXFLAGS} -c -o HeaderExploder.o HeaderExploder.cc

.PHONY: clean

clean:
	rm -f headexploder *.o
