#ifndef			HASH
#define			HASH

#include		<stdlib.h>
#include		<stdio.h>
#include		"wlist.h"

#define			HASH_SIZE_FACTOR 2

unsigned long	hashWord(const char *word);
t_wlist			*searchHashTable(t_wlist **, const unsigned int, const char *);
t_wlist			**createHashTable(t_wlist *, const unsigned int);
void			displayHashTable(t_wlist **, unsigned int);

#endif			/* WLIST */