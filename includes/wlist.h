#ifndef			WLIST
#define			WLIST

#include		<stdlib.h>
#include		<stdio.h>
#include		<fcntl.h>
#include		<string.h>

typedef struct	s_wlist {
	char		*word;
	unsigned int	occurencies;
	struct s_wordlist	*next;
}				t_wlist;

int				addWord(t_wlist **list, char *word);
int				clearWordList(t_wlist *list);
void			displayWords(t_wlist *list, unsigned int total_words);
t_wlist			*findWord(t_wlist *list, const char *word);

#endif			/* WLIST */
