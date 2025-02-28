NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS =	./mandatory/src/philo.c \
		./mandatory/src/components/monitor.c \
		./mandatory/src/components/philo_init.c \
		./mandatory/src/components/philo_routine.c \
		./mandatory/src/components/philo_utils.c \
		./mandatory/src/lib/ft_atof.c \
		./mandatory/src/lib/ft_atoi.c \
		./mandatory/src/lib/ft_putchar.c \
		./mandatory/src/lib/ft_putstr.c \
		./mandatory/src/lib/ft_strcmp.c \
		./mandatory/src/lib/ft_strlen.c \

OBJS = $(SRCS:.c=.o)


$(NAME): $(OBJS)
	$(CC)  $(OBJS) -o $(NAME) 


./mandatory/%.o: ./mandatory/%.c ./mandatory/includes/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean