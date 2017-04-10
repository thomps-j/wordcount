#include	"parser.h"

t_wlist	*parseDictFile(const char *filename) {
  t_wlist	*wlist = NULL;
  FILE		*fp;
  char		*buff = NULL, *new_word;
  ssize_t	len = 0, chars;

  if ((fp = fopen(filename, "r")) == NULL)
    return (NULL);
  
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
    if (findWord(wlist, buff) == NULL) {
      /* this is the first occurence for this word,
	 therefore it is added to the list
      */
      if ((new_word = malloc(sizeof(char) * (chars + 1))) == NULL)
       return (NULL);
     if (addWord(&wlist, strcpy(new_word, buff)) == EXIT_FAILURE)
       return (NULL);
   }
 }
 free(buff);
 fclose(fp);
 return (wlist);
}

int		parseInputStream(t_wlist **wlist, int fd) {
  char		c;
  char		*buff;
  ssize_t	len = 0, chars;
  unsigned int total_words = 0;
  t_wlist	*temp;

  if ((buff = malloc(sizeof(char))) == NULL)
    return (-1);
  *buff = '\0';
  
  /* the file is read char after char, which are appended to a buffer
     until a delimiter (' ' or '\0') is reached, after what the newly
     found word is compared with the dict words list
   */
  do {
    chars = read(fd, &c, 1);
    len++;
    if (c == ' ' || chars == 0) {
      /* if so, the word is complete and will be compared with the dict
       */
      total_words += 1;
      if ((temp = findWord(*wlist, buff)) != NULL)
      {
	  /* the word is part of the dict
	   */
       temp->occurencies += 1;
     }

      /* len and buff are reset for the next word iteration
       */
     len = 0;
     *buff = '\0';
   }
   else {
      /* otherwise the new char is added to the buffer
	       after a realloc
      */
    if ((buff = realloc(buff, sizeof(char) * (len + 1))) == NULL)
     return (-1);
   buff[len - 1] = c;
   buff[len] = '\0';      
 }
} while (chars > 0);
free(buff);
return (total_words);
}
