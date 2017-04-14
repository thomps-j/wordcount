#include	"parser.h"

unsigned int parseDictFile(t_wlist **wlist, const char *filename) {
  FILE		*fp;
  char		*buff = NULL;
  ssize_t	len = 0, chars;
  unsigned int total_words = 0;

  if ((fp = fopen(filename, "r")) == NULL)
    return (0);
  
  *wlist = NULL;
  while ((chars = getline(&buff, &len, fp)) != -1) {
    /* if the line starts with # or is empty, continue to the next one
     */
    if (buff[0] == '#' || buff[0] == '\n')
      continue;
    if (buff[chars - 1] == '\n') {
      /* replace '\n' character by EOL character ('\0')
	 and reduce word length (chars) accordingly
       */
      buff[chars - 1] = 0;
      chars -= 1;
    }
    if (addWord(wlist, strdup(buff)) == EXIT_FAILURE)
     return (0);
   total_words += 1;
 }
 free(buff);
 fclose(fp);
 return (total_words);
}

unsigned int		parseInputStream(t_wlist **table, const unsigned int size, const int fd) {
  char		c;
  char		*buff;
  ssize_t	len = 0, chars;
  unsigned int total_words = 0, size_table;
  t_wlist	*temp;

  if ((buff = malloc(sizeof(char))) == NULL)
    return (-1);
  *buff = '\0';
  size_table = size * HASH_SIZE_FACTOR;
  /* the file is read char after char, which are appended to a buffer
     until a delimiter (' ' or '\0') is reached, after what the newly
     found word is compared with the dict words list
   */
  do {
    chars = read(fd, &c, 1);
    printf("read >> '%c' (%zu)\n", c, chars);
    if (chars == 0 || c == '\0' || c == '\n' || c == ' ') {
      /* the character is a separator
      */
      if (len > 0) {
        /* the buffer is not empty, which means there is a word in it
        */
        if ((temp = searchHashTable(table, size_table, buff)) != NULL)
        {
        /* the word is part of the hash table
        */
          temp->occurencies += 1;
        }
        /* len and buff are reset for the next word iteration
        */
        len = 0;
        *buff = '\0';
        total_words++;
      }
    } else {
      /* otherwise the new char is added to the buffer
      after a realloc
      */
      len++;
      if ((buff = realloc(buff, sizeof(char) * (len + 1))) == NULL)
        return (-1);
      buff[len - 1] = c;
      buff[len] = '\0';
    }
  }  while (chars > 0);
  free(buff);
  return (total_words);
}
