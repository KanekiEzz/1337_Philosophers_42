NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  -O3
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

.PHONY: clean print_usage
print_usage:
	@echo "\033[1;34m\
        ##    ##    ###    ##    ## ######## ##    ## #### \\n\
        ##   ##    ## ##   ###   ## ##       ##   ##   ##  \\n\
        ##  ##    ##   ##  ####  ## ##       ##  ##    ##  \\n\
        #####    ##     ## ## ## ## ######   #####     ##  \\n\
        ##  ##   ######### ##  #### ##       ##  ##    ##  \\n\
        ##   ##  ##     ## ##   ### ##       ##   ##   ##  \\n\
        ##    ## ##     ## ##    ## ######## ##    ## #### \\033[0m\\n\
		\033[1;32mUsage:\033[0m\\n\
		\033[1;33m\\n\
			1:     ./fractol or ./fractol_bonus julia <real> <imaginary>\\n\
			or\\n\
			2:     ./fractol or ./fractol_bonus mandelbrot\\n\
			or\\n\
			3:     ./fractol or ./fractol_bonus burningship\\n\
			or\\n\
			4:     ./fractol or ./fractol_bonus tricorn\\n\
			or\\n\
			5:     ./fractol or ./fractol_bonus celtic\\033[0m\\n"