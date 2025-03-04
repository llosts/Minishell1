##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for the my_ls program
##

SRC 		=	src/usage.c					\
				src/environment.c			\
				src/shell.c					\
				src/builtins.c				\
				src/utils.c					\
				src/my_cd.c					\
				src/executor.c				\

MAIN_SRC 	=	src/main.c

TEST_SRC 	=	tests/test_usage.c			\
				tests/test_utils.c			\
				tests/test_shell.c			\
				tests/test_exectutor.c		\
				tests/test_builtins.c		\
				tests/test_environment.c	\

OBJ			=	$(SRC:.c=.o)				\
				$(MAIN_SRC:.c=.o)

TEST_OBJ	=	$(TEST_SRC:.c=.gcno)		\
				$(TEST_SRC:.c=.gcda)

CTESTS		=	-lcriterion --coverage
CGCOVR		=	gcovr --exclude tests ; gcovr --branch --exclude tests
CFLAGS		=   -Wall -Wextra -Werror -iquote include
LIBFLAGS	=	-L lib/ -lmy
LIB_MAKE	=	make -C lib/my
RM			=	rm -f
CC			=	gcc

TEST_NAME	=	unit_tests
NAME		=	mysh

all:			clib $(NAME)

clib:
		$(LIB_MAKE)

debug: 	CFLAGS += -g3 -fsanitize=address
debug: 	re

$(NAME):		$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBFLAGS)

$(TEST_NAME):	clean all
		$(CC) -o $(TEST_NAME) $(TEST_SRC) $(SRC) $(CTESTS)		\
		$(CFLAGS) $(LIBFLAGS)

tests_run:      $(TEST_NAME)
		./$(TEST_NAME) ; $(CGCOVR)

clean:
		$(RM) $(OBJ)
		$(RM) $(MAIN_OBJ)
		$(RM) $(TEST_OBJ)

fclean:			clean
		$(RM) $(NAME)
		$(RM) $(TEST_NAME)
		$(LIB_MAKE) fclean
		make -C ./bonus fclean

re:				fclean all

.PHONY:			all clean fclean all tests_run debug
