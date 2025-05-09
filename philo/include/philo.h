/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:23:14 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/13 03:52:44 by iezzam           ###   ########.fr       */
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

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	struct s_philo	*shared;
}		t_philosopher;

typedef struct s_philo
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				stop_simulation;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	shared_mutex;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}		t_philo;

int			parse_philo(int ac, char **av, t_philo *philo);
void		print_status(t_philosopher *philo, char *msg);
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
void		smart_sleep(long long time);
int			philo_init(t_philo *philo);
long long	get_time(void);

void		ft_putstr(char *s);
void		ft_putchar(char c);
double		ft_atof(const char *str);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);

#endif