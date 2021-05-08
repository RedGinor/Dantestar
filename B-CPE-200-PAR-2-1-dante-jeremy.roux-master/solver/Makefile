##
## EPITECH PROJECT, 2020
## makefile
## File description:
## makesfiles
##

SRC	=	src/main.c

NAME 	=	solver

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -W -Iincludes -g

LIB		=	-L lib -lib

all:	$(NAME)

make_lib:
	make -C lib all

$(NAME):	make_lib	$(OBJ)
	gcc $(OBJ) -o $(NAME) $(LIB)

clean:
	make -C lib clean
	rm -f $(OBJ)

fclean:	clean
	make -C lib fclean
	rm -f $(NAME)

re: 	fclean all