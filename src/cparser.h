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

#ifndef _PARSER_H
#define _PARSER_H

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct parser_kv {
	char *key;
	char *val;
};
struct parser_dict {
	int kvn;
	struct parser_kv *kv;
};

int parser_parse(int, char**, struct parser_dict *);
int parser_parseSpace(int, char**, struct parser_dict *);
int parser_hasKey(char *, struct parser_dict *);
int parser_getValue(char *, char *, struct parser_dict *);

int parse_dash(char *,  struct parser_dict *);
int parse_doubledash(char *,  struct parser_dict *);
void parser_free(struct parser_dict *);
void parser_print(int, struct parser_dict *);

#endif