/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/11 23:18:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	*death_monitor(void *arg)
{
	t_philosopher	*philo;
	long long		current_time;

	philo = (t_philosopher *)arg;
	while (1)
	{
		sem_wait(philo->shared->meal_check_sem);
		current_time = get_time();
		if (current_time - philo->last_meal_time > philo->shared->time_to_die)
		{
			print_status(philo, "died");
			sem_post(philo->shared->done_sem);
			exit(1);
		}
		sem_post(philo->shared->meal_check_sem);
		usleep(1000);
	}
	return (NULL);
}

void	eat(t_philosopher *philo)
{
	sem_wait(philo->shared->forks_sem);
	print_status(philo, "has taken a fork");
	sem_wait(philo->shared->forks_sem);
	print_status(philo, "has taken a fork");
	sem_wait(philo->shared->meal_check_sem);
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	if (philo->shared->eat_count > 0 && \
			philo->meals_eaten >= philo->shared->eat_count)
		sem_post(philo->shared->all_ate_sem);
	sem_post(philo->shared->meal_check_sem);
	smart_sleep(philo->shared->time_to_eat);
	sem_post(philo->shared->forks_sem);
	sem_post(philo->shared->forks_sem);
}

// int    check_if_done(t_philosopher *philo)
// {
//     struct timespec ts;
//     ts.tv_sec = 0;
//     ts.tv_nsec = 1000;

//     if (sem_timedwait(philo->shared->done_sem, &ts) == 0)
//     {
//         sem_post(philo->shared->done_sem);
//         return (1);
//     }
//     return (0);
// }

void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	death_thread;

	if (pthread_create(&death_thread, NULL, death_monitor, philo) != 0)
		exit(1);
	pthread_detach(death_thread);
	if (philo->id % 2 == 0)
		usleep(1000 * philo->shared->time_to_eat / 2);
	while (1)
	{
		// if (check_if_done(philo))
		//     exit(0);
		eat(philo);
		// if (check_if_done(philo))
		// exit(0);
		print_status(philo, "is sleeping");
		smart_sleep(philo->shared->time_to_sleep);
		// if (check_if_done(philo))
		//     exit(0);
		print_status(philo, "is thinking");
	}
}
