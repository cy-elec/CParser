#!/bin/bash

#add header
cp src/*.h bin/

## static

#compile
gcc -c -Wall -Werror -Wextra src/*.c
#archive
ar -rcs bin/libcparser.a *.o

#post-cleanup
rm *.o


## dynamic

#compile
gcc -fPIC -c -Wall -Werror -Wextra src/*.c
# create shared object
gcc -shared -Wl,-soname,libcparser.so -o bin/libcparser.so *.o
#post-cleanup
rm *.o