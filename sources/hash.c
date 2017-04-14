#include "hash.h"

unsigned long hashWord(const char *word) {
	/* hash function based on djb2 hash algorithm
	as it is short and very efficient for hash table use
	*/
	unsigned long hash = 5381;
	int c;

	while (c = (int) * word++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */		
	}
	return (hash);
}

t_wlist *searchHashTable(t_wlist **table, const unsigned int size, const char *word) {
	unsigned int hash;

	hash = hashWord(word);
	while (table[hash % size] != NULL) {
		/* search for the word that correspond to this hash in the table
		*/
		if (strcmp(table[hash % size]->word, word) == 0) {
			/* if the word is found in the hash table, return the pointer
			*/
			return (table[hash % size]);
		}
		/* else there was a collision, move forward
		*/
		hash++;
	}
	/* the word could not be found with its corresponding hash,
	therefore it is not in the hash table
	*/
	return (NULL);
}

t_wlist **createHashTable(t_wlist *list, const unsigned int size) {
	t_wlist **table;
	t_wlist *tmp;
	int hash;
	unsigned int i, max_index;

	/* the hash table will be 2 time bigger than the number of words
	to dilute the collisions
	*/
	max_index = size * HASH_SIZE_FACTOR;
	if ((table = malloc(sizeof(t_wlist *) * (max_index))) == NULL)
		return (NULL);
	for (i = 0; i < max_index; i++)
		table[i] = NULL;
	while (list != NULL) {
		/* for every word, get a hash code from word that will be
		used as index in the hash table
		*/
		hash = hashWord(list->word);
		while (table[hash % max_index] != NULL) {
			/* while there is collision, move forward
			*/
			if (strcmp(table[hash % max_index]->word, list->word) == 0) {
				/* if the collision is due to the same word already
				being in the hash table, don't add the word
				*/
				hash = -1;
				continue;
			}
			hash++;
		}
		if (hash == -1) {
			// continue with the next word
			continue;
		}	
		table[hash % max_index] = list;
		list = list->next;
	}
	return (table);
}

void displayHashTable(t_wlist **table, unsigned int size) {
	unsigned int i;

	for (i = 0; i < size; i++) {
		if (table[i] != NULL)
			printf("%i: '%s'\n", i, table[i]->word);
		else
			printf("%i: ---\n", i);
	}
}