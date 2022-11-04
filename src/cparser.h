/**
 * @file cparser.h
 * @author Felix Kröhnert (felix.kroehnert@online.de)
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _CPARSER_H
#define _CPARSER_H

#include <sys/types.h>
#include <fcntl.h>
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
} cparser_dict;

int cparser_parse(int, char**, cparser_dict *);
int cparser_parseSpace(int, char**, cparser_dict *);
int cparser_hasKey(char *, cparser_dict *);
int cparser_getValue(char *, char *, cparser_dict *);

int cparse_dash(char *,  cparser_dict *);
int cparse_doubledash(char *,  cparser_dict *);
void cparser_free(cparser_dict *);
void cparser_print(int, cparser_dict *);

#endif
