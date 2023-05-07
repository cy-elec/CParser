# CParser

A simple command line argument parser for c applications.
All resolved arguments can be accessed as a key-value pair and through the functions [cparser_hasKey()](#cparser_haskeychar-key-cparser_dict_t-input_dict) and [cparser_getValue()](#cparser_getvaluechar-key-char-dest-cparser_dict_t-input_dict).

## How to parse

There are two different options to resolve arguments:

1. [cparser_parse()](#cparser_parseint-argc-char-argv-cparser_dict_t-input_dict)
1. [cparser_parseSpace()](#cparser_parsespaceint-argc-char-argv-cparser_dict_t-input_dict)

Both functions require a key-value-pair [cparser_dict](#structures-and-types) to save the resolved arguments to.

## How to compile

* Windows:
    1. Download and install(adding the path variable) the most recent [WinLibs UCRT runtime](https://winlibs.com) and MinGW64(UCRT)
    1. Compile the code statically using gcc:

     ```bash
     gcc.exe -o <filename>.exe <filename>.c -l:libcparser.lib -L<libpath> -I<libpath>
     ```

* *nix:

    1. Verify the [Dependencies](#dependencies)
    1. Compile the code statically using gcc:

     ```bash
     gcc -o <filename>.o <filename>.c -l:libcparser.a -L<libpath> -I<libpath>
     ```

## Dependencies

```bash
unistd.h stdio.h stdlib.h string.h
```

## Structures and Types

```c
struct cparser_kv {
  char *key;  // key string
  char *val;  // value string
};
```

```c
typedef struct cparser_dict {
  int kvn;                // number of stored kv-pairs
  struct cparser_kv *kv;  // array that holds all kv-pairs
} cparser_dict_t;
```

## Functions

### `Parsing`

* #### `cparser_parse(int argc, char *argv[], cparser_dict_t *input_dict)`

  |||
  --|--
  |**description**|Parses key-value-pairs from a given input buffer of strings. Single dashes imply a single character argument. Their key is the first character after the dash, their value all other characters until the next whitespace or line end. Double dashes imply a word argument. Their key is the whole word - all characters until an equals sign or a whitespace or a line end, whichever comes first - after the double dash, their value all other character after the first equals sign until the next whitespace or line end.|
  |**params**|_number of buffer elements_ `int argc`, _pointer to buffer of strings_ `char *argv[]`, _pointer to a cparser dictionary_ `cparser_dict_t *input_dict`|
  |**return**|`int` - On success, return 1, otherwise return -1.|

* #### `cparser_parseSpace(int argc, char *argv[], cparser_dict_t *input_dict)`

  |||
  --|--
  |**description**|Same as [cparser_parse()](#cparser_parseint-argc-char-argv-cparser_dict_t-input_dict). However, double dash arguments also accept a single space instead of an equals sign.|
  |**params**|_number of buffer elements_ `int argc`, _pointer to buffer of strings_ `char *argv[]`, _pointer to a cparser dictionary_ `cparser_dict_t *input_dict`|
  |**return**|`int` - On success, return 1, otherwise return -1.|

### `Other`

* #### `cparser_free(cparser_dict_t *input_dict)`

  |||
  --|--
  |**description**|Frees the cparser dictionary.|
  |**params**|_pointer to a cparser dictionary_ `cparser_dict_t *input_dict`|
  |**return**|`void`|

* #### `cparser_print(int fd,  cparser_dict_t *input_dict)`
  
  |||
  --|--
  |**description**|Dumps the whole cparser dictionary to a specified file descriptor.|
  |**params**|_file descriptor_ `int fd`, _pointer to a cparser dictionary_ `cparser_dict_t *input_dict`|
  |**return**|`void`|

* #### `cparser_hasKey(char *key, cparser_dict_t *input_dict)`

  |||
  --|--
  |**description**|Checks if key has been resolved.|
  |**params**|_pointer to the requested key_ `char *key`, _pointer to a cparser dictionary_ `cparser_dict_t *input_dict`|
  |**return**|`int` - Return 1 when the requested key is part of the cparser dictionary, otherwise return 0.|

* #### `cparser_getValue(char *key, char *dest, cparser_dict_t *input_dict)`

  |||
  --|--
  |**description**|Obtains the value of a requested key and copies it to the destination location.|
  |**params**|_pointer to the requested key_ `char *key`, _pointer to destination buffer_ `char *dest`, _pointer to a cparser dictionary_ `cparser_dict_t *input_dict`|
  |**return**|`int` - On success, return 1, otherwise return 0.|
