/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:23:14 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/07 08:51:11 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>


# define SEM_FORKS "/forks"
# define SEM_LOCK "/print_lock"
# define SEM_MEAL "/meal_lock"
# define SEM_stop "/sim_stop"

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long long       last_meal;
    pid_t           pid;
    struct s_data   *data;
}   t_philo;

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_meals;
    long long       start_time;
    sem_t           *forks;
    sem_t           *print;
    sem_t           *stop;
    t_philo         *philos;
}   t_data;

// Main functions
long long   get_time(void);
void        ft_usleep(int ms);
void        init_data(t_data *data, int argc, char **argv);
void        init_philos(t_data *data);
void        philo_process(t_philo *philo);
void        start_simulation(t_data *data);
void        cleanup(t_data *data);

// Philosopher routines
void		philosopher_process(t_philo *philo);
void		*monitor_routine(void *arg);
void		eat(t_philo *philo);

// Utility functions
long long	get_time(void);
void		smart_sleep(long long time);
void		print_status(t_philo *philo, char *msg);

// lib
double		ft_atof(const char *str);
void		ft_putchar(char c);
void		ft_putstr(char *s);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);

#endif