#!/bin/bash

#compile
gcc -c -Wall -Werror -Wextra src/*.c

#archive
ar -rcs bin/libcparser.a *.o

#add header
cp src/*.h bin/

#post-cleanup
rm *.o