# Wordcount

[Github repository](https://github.com/thomps-j/wordcount.git)

### Features

  - Read **dictfile** line by line to populate a **hash table**
  - Read **inputfile(s)** given as parameters or **standard input** if none is given
  - Count words occurences referenced by the dictfile in the given input stream
  - Tested with *Valgrind* for memory leak and error

### Building

To compile the project, run the following command line in a Terminal:

```sh
$ make
```

To clean objet files:

```sh
$ make clean
```

To clean object files and executable:

```sh
$ make fclean
```

To rerun compilation:

```sh
$ make re
```

### Usage

To use wordcount with inputfile(s):
```sh
$ ./wordcount dictfile [inputfile ...]
```

To use wordcount using standard input (examples):
```sh
$ ./wordcount dictfile
# the program will wait for user input
$ cat inputfile | ./wordcount dictfile
# the program will be fed through the pipe
```

*Note: missing a dictfile will immediately end the program*

### Description and limitations

In accordance with the prerequisites of the project, the program has been developped as follows:

  - The dictfile parser
    - *parseDictFile()* function in *sources/parser.c*
    - The parser **requires** one one per line as defined in the prerequisites (no space)
    - Reads the file line by line using *getline()* function, which requires the GNU C Library
    - *getline()* was used to speed up development time. Another way of reading the content would have been to use a reading buffer using the *read()* system function
    - The parser checks for duplicates before adding a new word
- The input parser
    - *parseInputStream()* function in *sources/parser.c*
    - The parser **requires** blank space to separates each word as defined in the prerequisites (therefore '*\n'* is not a separator)
    - Read the input stream character after character using *read()* system function and concatenates the character in a buffer. Since the buffer ultimatly contains a full word, the program performs word comparison only when needed instead of every new character
    - This parsing method was chosen since the prerequisites state that the input stream may have no limits *and* to speed up development time
- The hash table functions
    - Functions in *sources/hash.h*, definitions contained in *includes/hash.h*
    - *createHashTable()* classifies the words from the dict in a hash table
    - *hashWord()* is the hash function, based on **djb2** created by Daniel J. Bernstein, as it is especially efficient with collisions and CPU usage on large dictfiles 
- The words chained list
    - Function definitions contained in *includes/wlist.h*
    - *sources/wlist.c* contains the functions for words list edition
    - Used to concatenate words contained in *wordfile*
    - Required to create the hash table