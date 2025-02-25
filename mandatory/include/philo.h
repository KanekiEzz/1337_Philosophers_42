#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#include <pthread.h>
#include <sys/time.h>


typedef struct s_philosopher
{
    int             id;
    pthread_t       thread;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_philo  *shared;
}   t_philosopher;

typedef struct s_philo
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             eat_count;
    long long       start_time;
    int             stop_simulation;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher   *philosophers;
}   t_philo;

void *monitor_routine(void *arg);
long long   get_time(void);
void        smart_sleep(long long time);
void        print_status(t_philosopher *philo, char *msg);
void        *philosopher_routine(void *arg);
int         philo_init(t_philo *philo);
int         parse_philo(int ac, char **av, t_philo *philo);



//lib
double	ft_atof(const char *str);
void	ft_putchar(char c);
void	ft_putstr(char *s);
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
int	ft_atoi(const char *str);

#endif