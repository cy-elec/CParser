#include "cparser.h"

cparser_dict resolved_args;
int main(int argc, char *argv[]) {
	cparser_parseSpace(argc, argv, &resolved_args);
	cparser_print(fileno(stdout), &resolved_args);

	return 0;
}