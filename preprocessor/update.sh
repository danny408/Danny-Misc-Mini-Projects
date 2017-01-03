#!/bin/bash
g++ preprocessor2.cpp -O0 -g -o preprocessor2-11 -std=c++11 -Wall
g++ preprocessor2.cpp -O0 -g -o preprocessor2-03 -std=c++03 -Wall
g++ preprocessor3.cpp -O0 -g -o preprocessor3 -Wall


gcc -c preprocessor2.cpp -o preprocessor2.o
gcc -c preprocessor3.cpp -o preprocessor3.o

ar -cvq /home/danny/dannyQuestions/libdanny.a preprocessor2.o
ar -cvq /home/danny/dannyQuestions/libdanny.a preprocessor3.o

ar -t /home/danny/dannyQuestions/libdanny.a