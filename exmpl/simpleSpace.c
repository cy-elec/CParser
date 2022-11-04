/**
 * @file simpleSpace.c
 * @author Felix Kröhnert (felix.kroehnert@online.de)
 * @brief Command line argument parser with space recognition 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "cparser.h"

cparser_dict resolved_args;
int main(int argc, char *argv[]) {
	cparser_parseSpace(argc, argv, &resolved_args);
	cparser_print(fileno(stdout), &resolved_args);

	return 0;
}