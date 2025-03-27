/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 23:23:14 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/15 06:09:26 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_philosopher
{
	int				id;
	pid_t			pid;
	int				meals_eaten;
	long long		last_meal_time;
	struct s_philo	*shared;
}		t_philosopher;

typedef struct s_philo
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long long		start_time;
	int				stop_simulation;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*meal_check_sem;
	sem_t			*done_sem;
	sem_t			*all_ate_sem;
	t_philosopher	*philosophers;
	pid_t			*pids;
}		t_philo;

// Process and monitor functions
void		*monitor_routine(void *arg);
void		philosopher_routine(t_philosopher *philo);
void		cleanup_child_process(t_philosopher *philo);

// Time and utility functions
long long	get_time(void);
void		smart_sleep(long long time);
void		print_status(t_philosopher *philo, char *msg);

// Initialization
int			initialize_philosophers(t_philo *philo);
int			philo_init(t_philo *philo);
int			parse_philo(int ac, char **av, t_philo *philo);

// Monitor
int			start_simulation(t_philo *philo);

// Semaphore utilities
void		create_semaphores(t_philo *philo);
void		close_semaphores(t_philo *philo);

// Cleanup function
void		philo_cleanup(t_philo *philo);
// lib
double		ft_atof(const char *str);
void		ft_putchar(char c);
void		ft_putstr(char *s);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);

#endif