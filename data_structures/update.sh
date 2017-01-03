#!/bin/bash


# g++ ds1.hpp -O0 -g -o ds1 -Wall
# gcc ds2.c -O0 -g -o ds2 -Wall
# g++ ds3.cpp -O0 -g -o ds3 -Wall
# g++ ds4.cpp -O0 -g -o ds4 -Wall
# g++ ds5.cpp -O0 -g -o ds5 -Wall
# g++ ds6.cpp -O0 -g -o ds6 -Wall

g++ -c ds1.cpp -O0 -o ds1.o
gcc -c ds2.c -O0 -o ds2.o 
# g++ ds3.cpp -O0 -g -o ds3.o -Wall
# g++ ds4.cpp -O0 -g -o ds4.o -Wall
# g++ ds5.cpp -O0 -g -o ds5.o -Wall
# g++ ds6.cpp -O0 -g -o ds6.o -Wall




ar -crv /home/danny/dannyQuestions/libdanny.a ds1.o
ar -crv /home/danny/dannyQuestions/libdanny.a ds2.o
# ar -cvq /home/danny/dannyQuestions/libdanny.a ds3.o
# ar -cvq /home/danny/dannyQuestions/libdanny.a ds4.o
# ar -cvq /home/danny/dannyQuestions/libdanny.a ds5.o
# ar -cvq /home/danny/dannyQuestions/libdanny.a ds6.o

ar -t /home/danny/dannyQuestions/libdanny.a