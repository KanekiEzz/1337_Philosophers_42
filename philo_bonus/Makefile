NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror   -g -fsanitize=thread
RM = rm -f

# ./src/components/monitor.c \

SRCS =	./src/philo.c \
		./src/components/philo_init.c \
		./src/components/philo_routine.c \
		./src/components/philo_utils.c \
		./src/lib/ft_atof.c \
		./src/lib/ft_putchar.c \
		./src/lib/ft_putstr.c \
		./src/lib/ft_strcmp.c \
		./src/lib/ft_strlen.c \

OBJS = $(SRCS:.c=.o)


$(NAME): $(OBJS)
	$(CC)  $(OBJS) -o  $(NAME)  -g -fsanitize=thread

%.o: %.c ./include/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all
