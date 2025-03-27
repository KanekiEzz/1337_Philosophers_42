NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f


SRCS =	./src/philo_bonus.c \
		./src/components/monitor_bonus.c \
		./src/components/philo_init_bonus.c \
		./src/components/philo_routine_bonus.c \
		./src/components/philo_utils_bonus.c \
		./src/lib/ft_atof_bonus.c \
		./src/lib/ft_putchar_bonus.c \
		./src/lib/ft_putstr_bonus.c \
		./src/lib/ft_strcmp_bonus.c \
		./src/lib/ft_strlen_bonus.c \

OBJS = $(SRCS:.c=.o)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o  $(NAME)  -lpthread

%.o: %.c ./include/philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all
