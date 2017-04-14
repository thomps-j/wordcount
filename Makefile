NAME	=	wordcount

SRCDIR	=	sources

INCDIR	=	-Iincludes

SRC	=	$(SRCDIR)/main.c \
		$(SRCDIR)/wlist.c \
		$(SRCDIR)/parser.c \
		$(SRCDIR)/hash.c \

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W $(INCDIR)

LDFLAGS	=	-lpthread

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		gcc $(OBJ) $(LDFLAGS) -o $(NAME)

clean	:
		rm -rf $(OBJ)

fclean	:	clean
		rm -rf $(NAME)

re	:	fclean all
