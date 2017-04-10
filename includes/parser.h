#ifndef			PARSER
#define			PARSER

#include		<unistd.h>
#include		<string.h>
#include		"wlist.h"

t_wlist			*parseDictFile(const char *);
int				parseInputStream(t_wlist **, int);

#endif			/* PARSER */
