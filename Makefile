.PHONEY: all clean fclean re

NAME	=	philosophers

HEADERS = 	./includes
PARSER	= 	
UTILS	= 	

SRC		=	src/main.c\
			$(PARSER:%.c=./src/parser/%.c)\
			$(UTILS:%.c=./src/utils/%.c)

CC		=	gcc
DBG		=	-g
FLAGS	=	#-Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -I$(HEADERS) -o $(NAME) $(DBG) $(FLAGS)

clean:
	@rm -rf *.o

fclean: clean
	@-rm -f $(NAME)

re: fclean all

