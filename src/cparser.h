/**
 * @file cparser.h
 * @author Felix Kröhnert (felix.kroehnert@online.de)
 * @brief Command line argument parser interface
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef _CPARSER_H
#define _CPARSER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct cparser_kv {
	char *key;
	char *val;
};
typedef struct cparser_dict {
	int kvn;
	struct cparser_kv *kv;
} cparser_dict_t;

int cparser_parse(int argc, char *argv[], cparser_dict_t *input_dict);
int cparser_parseSpace(int argc, char *argv[], cparser_dict_t *input_dict);
int cparser_hasKey(char *key, cparser_dict_t *input_dict);
int cparser_getValue(char *key, char *dest, cparser_dict_t *input_dict);

static int cparse_dash(char *argv,  cparser_dict_t *input_dict);
static int cparse_doubledash(char *argv,  cparser_dict_t *input_dict);
void cparser_free(cparser_dict_t *input_dict);
void cparser_print(int fd,  cparser_dict_t *input_dict);

#endif
