.PHONEY: all clean fclean re

NAME	=	philosophers

HEADERS = 	./includes

SRC		=	src/main.c src/utils.c

CC		=	gcc
DBG		=	-g
FLAGS	=	#-Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -I$(HEADERS) -o $(NAME) $(DBG) $(FLAGS) -lpthread

clean:
	@rm -rf *.o

fclean: clean
	@-rm -f $(NAME)

re: fclean all

