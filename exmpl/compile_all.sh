#!/bin/bash

gcc -o bin/simpleSpace.o simpleSpace.c -l:libcparser.a -L../bin -I../bin

strip -s bin/*.o