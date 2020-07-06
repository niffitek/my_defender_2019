##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## for evalexpr
##

SRC     =   src/main.c \
            src/event.c \
            src/text.c \
            src/create.c \
            src/map.c \
            src/enemy.c \
            src/move_enemy.c \
            src/random.c \
            src/tower_create.c \
            src/projectile_create.c \
            src/tower.c \
            src/hud.c \
            src/game.c \
            src/tower_standard.c \
            src/destroy.c \
            src/game_over.c

#CFLAGS  += -W -Wall -Wextra -Werror -g3

OBJ	=	$(SRC:.c=.o)

NAME	=	my_defender

RM	=	rm -f

VALGRIND    =   -g3

all:		$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ) -l csfml-graphics -l csfml-system -l csfml-audio \
		$(VALGRIND)
		./random.sh > seed

clean:
	$(RM) $(OBJ) seed

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
