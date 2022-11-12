#!/bin/bash

#add header
cp src/*.h bin/

## static

#compile
gcc.exe -c -Wall -Werror -Wextra src/*.c
#archive
ar -rcs bin/libcparser.lib *.o

#post-cleanup
rm *.o
