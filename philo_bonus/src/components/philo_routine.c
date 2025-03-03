/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/28 22:59:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork 🍽️");
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork 🍽️");
		pthread_mutex_lock(philo->right_fork);
	}
	print_status(philo, "has taken a fork 🍽️");
	pthread_mutex_lock(&philo->meal_mutex);
	print_status(philo, "is eating 🍝");
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleep(philo->shared->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat_one_philo(t_philosopher *philo)
{
	if (philo->shared->number_of_philosophers == 1)
	{
		print_status(philo, "has taken a fokr 🍽️");
		smart_sleep(philo->shared->time_to_die);
		print_status(philo, "dided 💀");
	}
	return ;
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				should_stop;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->stop_mutex);
		should_stop = philo->shared->stop_simulation;
		pthread_mutex_unlock(&philo->shared->stop_mutex);
		if (should_stop)
			break ;
		if (philo->shared->number_of_philosophers == 1)
		{
			eat_one_philo(philo);
			return (NULL);
		}
		eat(philo);
		print_status(philo, "is sleeping 😴");
		smart_sleep(philo->shared->time_to_sleep);
		print_status(philo, "is thinking 🤔");
	}
	return (NULL);
}
