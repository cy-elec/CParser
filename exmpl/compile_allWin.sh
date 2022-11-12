#!/bin/bash

gcc.exe -o bin/simpleSpace.exe simpleSpace.c -l:libcparser.lib -L../bin -I../bin

strip.exe -s bin/*.exe