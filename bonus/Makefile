##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for the my_ls program
##

SRC 		=	../src/usage.c				\
				../src/environment.c		\
				shell.c						\
				../src/builtins.c			\
				../src/utils.c				\
				../src/my_cd.c				\
				../src/executor.c			\

MAIN_SRC 	=	../src/main.c

OBJ			=	$(SRC:.c=.o)				\
				$(MAIN_SRC:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.gcno)		\
				$(TEST_SRC:.c=.gcda)

CFLAGS		=   -Wall -Wextra -Werror -iquote ../include
LIBFLAGS	=	-L ../lib/ -lmy
LIB_MAKE	=	make -C ../lib/my
RM			=	rm -f
CC			=	gcc
CP 			=	cp -f

NAME		=	mysh

all:			clib $(NAME)

clib:
		$(LIB_MAKE)
		$(CP) bonus.h ../include

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS)

clean:
		$(RM) $(OBJ)
		$(RM) $(MAIN_OBJ)
		$(RM) $(TEST_OBJ)

fclean:			clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)
		$(RM) ../include/bonus.h
		$(LIB_MAKE) fclean

re:				fclean all


.PHONY:			all clean fclean all
