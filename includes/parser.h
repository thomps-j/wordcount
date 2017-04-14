#ifndef			PARSER
#define			PARSER

#include		<unistd.h>
#include		<string.h>
#include		"wlist.h"
#include		"hash.h"

unsigned int	parseDictFile(t_wlist **, const char *);
unsigned int	parseInputStream(t_wlist **, const unsigned int, const int);

#endif			/* PARSER */
