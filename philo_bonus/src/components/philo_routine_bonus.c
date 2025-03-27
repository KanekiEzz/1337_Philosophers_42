/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/15 06:09:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

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
			return (NULL);
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

void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	death_thread;

	if (pthread_create(&death_thread, NULL, death_monitor, philo) != 0)
	{
		sem_close(philo->shared->forks_sem);
		sem_close(philo->shared->print_sem);
		sem_close(philo->shared->meal_check_sem);
		sem_close(philo->shared->done_sem);
		sem_close(philo->shared->all_ate_sem);
		exit(1);
	}
	pthread_detach(death_thread);
	if (philo->id % 2 == 0)
		usleep(1000 * philo->shared->time_to_eat / 2);
	while (1)
	{
		eat(philo);
		print_status(philo, "is sleeping");
		smart_sleep(philo->shared->time_to_sleep);
		print_status(philo, "is thinking");
	}
}
