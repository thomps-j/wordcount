#include	"wlist.h"
#include	"parser.h"

int		main(int argc, char **argv) {
  t_wlist	*list = NULL;
  unsigned int total_words = 0;
  int		i, fd;

  if (argc < 2) {
    /* no dictfile given as parameter, abort
    */
    return (EXIT_FAILURE);
  }
  if ((list = parseDictFile(argv[1])) == NULL)
    return (EXIT_FAILURE);
  if (argc == 2) {
    /* read standard input and count words occurencies
     */
    total_words = parseInputStream(&list, 0);
  }
  else {
    for (i = 2; i < argc; i++) {
      /* open each inputfile and count words occurencies
       */
      fd = open(argv[i], O_RDONLY);
      total_words += parseInputStream(&list, fd);
      close(fd);
    }
  }
  displayWords(list, total_words); // display the words occurcencies
  clearWordList(list); // words list is freed before exit
  return (EXIT_SUCCESS);
}
