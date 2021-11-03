.PHONEY: all clean fclean re

NAME	=	philosophers
CC		=	gcc
CFLAGS	=	#-Werror -Wextra -Wall

HEADERS = 	./includes
SOURCES	=	main.c args_parser.c philo_states.c time_utils.c print_utils.c
SRC		=	$(SOURCES:%.c=./src/%.c)\

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -I$(HEADERS) -o $(NAME) $(CFLAGS) -pthread

clean:
	@rm -rf *.o

fclean: clean
	@-rm -f $(NAME)

re: fclean all
