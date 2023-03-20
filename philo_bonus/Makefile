NAME = philo_bonus
SRCS = philo_bonus.c utils.c utils2.c alloc_structs.c monitor.c
OBJS = $(SRCS:.c=.o)
HEADER = philo_bonus.h
CC = gcc -pthread
FLAGS = -Wall -Werror -Wextra

all: philo_bonus

bonus: philo_bonus

philo_bonus:
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus