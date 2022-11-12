# CParser

## How to compile
* Windows:
    1) Download and install(adding the path variable) the most recent [WinLibs UCRT runtime](https://winlibs.com) and MinGW64(UCRT)
    2) Compile the code statically using gcc: 
	    ```
	    gcc.exe -o <filename>.exe <filename>.c -l:libcparser.lib -lws2_32 -L<libpath> -I<libpath>
	    ```
* *nix:
    1) Verify the [Dependencies](#dependencies)
	2) Compile the code statically using gcc:
	    ```
	    gcc -o <filename>.o <filename>.c -l:libcparser.a -lws2_32 -L<libpath> -I<libpath>
	    ```

## Dependencies
```
unistd.h stdio.h stdlib.h string.h
```