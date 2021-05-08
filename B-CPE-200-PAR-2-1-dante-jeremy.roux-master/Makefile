##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

GEN	=	generator/

SOL	=	solver/

all:
	make -C $(GEN)
	make -C $(SOL)

clean:
	make clean -C $(GEN)
	make clean -C $(SOL)

fclean:
	make fclean -C $(GEN)
	make fclean -C $(SOL)

re:	
	clean fclean all

.PHONY:	all clean fclean re