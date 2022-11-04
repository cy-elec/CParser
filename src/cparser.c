/**
 * @file cparser.c
 * @author Felix Kröhnert (felix.kroehnert@online.de)
 * @brief 
 * @version 0.1
 * @date 2022-10-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "cparser.h"


int parser_parse(int argc, char *argv[], struct parser_dict *input_dict) {
	if(input_dict->kv)
		parser_free(input_dict);
	input_dict->kvn = 0;
	
	for(int i=1; i<argc; i++) {
		if(argv[i][0]=='-') {
			
			if(argv[i][1]=='-') {
				if(parse_doubledash(&argv[i][2], input_dict)) goto errexit;
			}
			else {
				if(parse_dash(&argv[i][1], input_dict)) goto errexit;
			}
		}
	}

	return 0;

	errexit:
	if(input_dict)
		parser_free(input_dict);
	return -1;
}

int parser_parseSpace(int argc, char *argv[], struct parser_dict *input_dict) {

	char *margv[argc];
	int margc = argc;
	for(int i=0; i<argc; i++) {
		margv[i-(argc-margc)] = malloc(strlen(argv[i])+1);
		if(!margv[i-(argc-margc)]) goto errexit;
		memcpy(margv[i-(argc-margc)], argv[i], strlen(argv[i]));
		margv[i-(argc-margc)][strlen(argv[i])] = 0;

		if(argv[i][0]=='-'&&strlen(argv[i])>1&&argv[i][1]=='-') {
			for(size_t d=0; d<strlen(argv[i]); d++) {
				if(argv[i][d] == '=') {
					goto normal_arg;
				}
			}
			
			if(i<argc-1) {
				margv[i-(argc-margc)] = realloc(margv[i-(argc-margc)], strlen(argv[i])+strlen(argv[i+1])+2);
				if(!margv[i-(argc-margc)]) goto errexit;
				memcpy(&margv[i-(argc-margc)][strlen(argv[i])+1], argv[i+1], strlen(argv[i+1]));
				margv[i-(argc-margc)][strlen(argv[i])+strlen(argv[i+1])+1] = 0;
				margv[i-(argc-margc)][strlen(argv[i])] = '=';
				margc--;
				i++;
			}
		}
		 

		normal_arg:;
	}

	int rval = parser_parse(margc, margv, input_dict);

	for(int i=0; i<margc; i++) {
		free(margv[i]);
		margv[i]=NULL;
	}

	return rval;

	errexit:
	if(input_dict)
		parser_free(input_dict);
	return -1;
}

int parser_hasKey(char *key, struct parser_dict *input_dict) {
	if(!key||!input_dict) 
		return 0;
	
	for(int i=0; i<input_dict->kvn; i++) {
		if(strcmp(input_dict->kv[i].key, key)==0) return 1;
	}
	return 0;
}

int parser_getValue(char *key, char *dest, struct parser_dict *input_dict) {
	if(!key||!input_dict||!dest) 
		return 0;
	
	for(int i=0; i<input_dict->kvn; i++) {
		if(strcmp(input_dict->kv[i].key, key)==0) {
			memcpy(dest, input_dict->kv[i].val, strlen(input_dict->kv[i].val));
			dest[strlen(input_dict->kv[i].val)]=0;
			return 1;
		}
	}
	dest[0] = 0;
	return 0;
}


int parse_dash(char *argv,  struct parser_dict *input_dict) {
	if(!argv || !input_dict)
		return 0;
	
	int ci = input_dict->kvn;
	input_dict->kvn++;
	void *temp = realloc(input_dict->kv, input_dict->kvn * sizeof(struct parser_kv));
	if(!temp)
		return -1;
	input_dict->kv = temp;
	
	input_dict->kv[ci].key = malloc(2);
	if(!input_dict->kv[ci].key) return -1;
	input_dict->kv[ci].key[0] = argv[0]; 
	input_dict->kv[ci].key[1] = 0;

	int tl = strlen(argv)-1;
	if(tl>0) {
		input_dict->kv[ci].val = malloc(tl);
		if(!input_dict->kv[ci].val) return -1;
		memcpy(input_dict->kv[ci].val, &argv[1], tl); 
		input_dict->kv[ci].val[tl] = 0;
	}
	else {
		input_dict->kv[ci].val = malloc(1);
		if(!input_dict->kv[ci].val) return -1;
		input_dict->kv[ci].val[0] = 0;
	}
	return 0;
}

int parse_doubledash(char *argv,  struct parser_dict *input_dict) {
	if(!argv || !input_dict)
		return 0;
	
	int offset = 0;
	while(argv[offset]!=0&&argv[offset]!='=') {
		offset++;
	}
	if(offset<1) {
		return 0;
	}

	int ci = input_dict->kvn;
	input_dict->kvn++;
	void *temp = realloc(input_dict->kv, input_dict->kvn * sizeof(struct parser_kv));
	if(!temp)
		return -1;
	input_dict->kv = temp;
	input_dict->kv[ci].key = malloc(offset+1);
	if(!input_dict->kv[ci].key) return -1;
	memcpy(input_dict->kv[ci].key, argv, offset); 
	input_dict->kv[ci].key[offset] = 0;

	int tl = strlen(argv)-1;
	if(tl>0 && offset<tl) {
		input_dict->kv[ci].val = malloc(tl-offset+1);
		if(!input_dict->kv[ci].val) return -1;
		memcpy(input_dict->kv[ci].val, &argv[offset+1], tl-offset); 
		input_dict->kv[ci].val[tl-offset] = 0;
	}
	else {
		input_dict->kv[ci].val = malloc(1);
		if(!input_dict->kv[ci].val) return -1;
		input_dict->kv[ci].val[0] = 0;
	}
	return 0;
}

void parser_free(struct parser_dict *input_dict) {
	if(input_dict) {
		if(input_dict->kv) {
			for(int i=0; i<input_dict->kvn; i++) {
				if(input_dict->kv[i].key) {
					free(input_dict->kv[i].key);
					input_dict->kv[i].key=NULL;
				}
				if(input_dict->kv[i].val) {
					free(input_dict->kv[i].val);
					input_dict->kv[i].val=NULL;
				}
			}
			free(input_dict->kv);
			input_dict->kv=NULL;
		}
	}
}

void parser_print(int fd,  struct parser_dict *input_dict) {
	FILE *fp = fdopen(dup(fd), "w");
	if(!input_dict || !input_dict->kv) {
		fprintf(fp, "NULL\n");
		return;
	}

	fprintf(fp, "[%d]\n{\n", input_dict->kvn);
	for(int i=0; i<input_dict->kvn; i++) {
		fprintf(fp, "   [\"%s\" : \"%s\"]\n", input_dict->kv[i].key, input_dict->kv[i].val);
	}
	fprintf(fp, "}\n");
	fclose(fp);
	return;
}