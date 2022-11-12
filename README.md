# CParser

A simple command line argument parser for c applications.
All resolved arguments can be accessed as a key-value pair and through the functions `cparser_hasKey` and `cparser_getValue`.

## How to parse
There are two different options to resolve arguments:
1) "normal" evaluation with `cparser_parse(argc, argv, cparser_dict_t)`:
    * resolve single dash as single character argument
		* key : first character after dash
		* value : all other characters until next whitespace
	* resolve double dash as word argument
		* key : all characters until equals sign or whitespace, whichever comes first
		* value : all other characters after the first equals sign until next whitespace
2) "Space" evaluation with `cparser_parseSpace(argc, argv, cparser_dict_t)`:
	* resolve single dash same as "normal" evaluation
	* resolve double dash same as "normal" evaluation but also accept spaces instead of the equals sign
   

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