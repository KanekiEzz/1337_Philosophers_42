#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_philo
{
    int id;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
}	t_philo;

//lib
double	ft_atof(const char *str);
void	ft_putchar(char c);
void	ft_putstr(char *s);
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int	ft_atoi(const char *str);

#endif