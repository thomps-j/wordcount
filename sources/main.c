#include  "wlist.h"
#include  "parser.h"
#include  "hash.h"

int		main(int argc, char **argv) {
  t_wlist	*list = NULL;
  t_wlist **hashtable;
  unsigned int total_words = 0, size = 0;
  int		i, fd;

  if (argc < 2) {
    /* no dictfile given as parameter, abort
    */
    return (EXIT_FAILURE);
  }
  if ((size = parseDictFile(&list, argv[1])) == 0)
    return (EXIT_FAILURE);
 
  /* create the hash table from the list of words
  */
  hashtable = createHashTable(list, size);
  if (argc == 2) {
    /* read standard input and count words occurencies
     */
    total_words = parseInputStream(hashtable, size, 0);
  }
  else {
    for (i = 2; i < argc; i++) {
      /* open each inputfile and count words occurencies
       */
      fd = open(argv[i], O_RDONLY);
      total_words += parseInputStream(hashtable, size, fd);
      close(fd);
    }
  }
  displayWords(list, total_words); // display the words occurcencies
  clearWordList(list); // words list is freed before exit
  free(hashtable);
  return (EXIT_SUCCESS);
}
