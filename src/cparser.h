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
struct cparser_dict {
	int kvn;
	struct cparser_kv *kv;
};

int cparser_parse(int, char**, struct cparser_dict *);
int cparser_parseSpace(int, char**, struct cparser_dict *);
int cparser_hasKey(char *, struct cparser_dict *);
int cparser_getValue(char *, char *, struct cparser_dict *);

int cparse_dash(char *,  struct cparser_dict *);
int cparse_doubledash(char *,  struct cparser_dict *);
void cparser_free(struct cparser_dict *);
void cparser_print(int, struct cparser_dict *);

#endif
