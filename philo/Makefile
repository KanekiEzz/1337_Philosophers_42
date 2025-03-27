NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS =	./src/philo.c \
		./src/components/monitor.c \
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
	$(CC) $(CFLAGS) $(OBJS) -o  $(NAME)

%.o: %.c ./include/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all
