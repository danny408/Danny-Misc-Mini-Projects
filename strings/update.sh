#!/bin/bash
g++ string1.cpp -o string1 -Wall
g++ string2.cpp -o string2 -Wall
g++ string5.cpp -O0 -g -o string5 -Wall
g++ string6.cpp -O0 -g -o string6 -Wall
g++ string5_ucs4.cpp -O0 -g -o string5_ucs4 -Wall
g++ string6_ucs4.cpp -O0 -g -o string6_ucs4 -Wall
g++ string6_v2.cpp -O0 -g -o string6_v2 -Wall
g++ test.cpp -o test -Wall


g++ string1.cpp -o string1.o
g++ string2.cpp -o string2.o
g++ string5.cpp -O0 -g -o string5.o
g++ string6.cpp -O0 -g -o string6.o
g++ string5_ucs4.cpp -O0 -g -o string5_ucs4.o
g++ string6_ucs4.cpp -O0 -g -o string6_ucs4.o
g++ string6_v2.cpp -O0 -g -o string6_v2.o


ar -cvq /home/danny/dannyQuestions/libdanny.a string1.o
ar -cvq /home/danny/dannyQuestions/libdanny.a string2.o
ar -cvq /home/danny/dannyQuestions/libdanny.a string5.o
ar -cvq /home/danny/dannyQuestions/libdanny.a string6.o
ar -cvq /home/danny/dannyQuestions/libdanny.a string5_ucs4.o
ar -cvq /home/danny/dannyQuestions/libdanny.a string6_ucs4.o
ar -cvq /home/danny/dannyQuestions/libdanny.a string6_v2.o

ar -t /home/danny/dannyQuestions/libdanny.a