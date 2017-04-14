#include	"wlist.h"

void		displayWords(t_wlist *list, unsigned int total_words) {
  while (list != NULL) {
    printf("%i\t%s\n", list->occurencies, list->word);
    list = list->next;
  }
  printf("%i\ttotal words\n", total_words);
}

t_wlist	*findWord(t_wlist *list, const char *word) {
  while (list != NULL) {
    if (strcmp(list->word, word) == 0) {
      /* if this element word is the same as searched word
       */
      return (list);
    }
    list = list->next; // iterate to the next element
  }
  return (NULL); // no occurence found
}

int		addWord(t_wlist **list, char *word) {
  t_wlist	*new;

  // a new element of the list is populated
  if ((new = malloc(sizeof(t_wlist))) == NULL)
    return (EXIT_FAILURE); // error while mallocing a new t_wlist
  new->word = word;
  new->occurencies = 0;
  new->next = NULL;

  if (*list == NULL) { // if this is the first element of the list 
    *list = new;
  }
  else {
    /* otherwise the list already exists and the element must be
       appended to the end of the list
    */
    t_wlist	*tmp;

    tmp = *list;
    while (tmp->next != NULL)
      tmp = tmp->next; // iterating over the list until the last element
    tmp->next = new; // the new element is added to the end of the list
  }
  return (EXIT_SUCCESS);
}

int		clearWordList(t_wlist *list) {
  t_wlist	*temp;

  while (list != NULL) {
    temp = list->next;
    /* free all allocations
    */
    free(list->word);
    free(list);
    list = temp; // moves to the next iteration
  }
  return (EXIT_SUCCESS);
}
