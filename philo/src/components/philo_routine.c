/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/14 23:29:57 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meal_mutex);
	print_status(philo, "is eating");
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleep(philo->shared->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	return ;
}

void	eat_one_philo(t_philosopher *philo)
{
	if (philo->shared->number_of_philosophers == 1)
	{
		print_status(philo, "has taken a fork");
		smart_sleep(philo->shared->time_to_die);
		print_status(philo, "died");
	}
	return ;
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				should_stop;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		smart_sleep(philo->shared->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->stop_mutex);
		should_stop = philo->shared->stop_simulation;
		pthread_mutex_unlock(&philo->shared->stop_mutex);
		if (should_stop)
			break ;
		if (philo->shared->number_of_philosophers == 1)
			return (eat_one_philo(philo), NULL);
		(eat(philo), pthread_mutex_lock(&philo->shared->stop_mutex));
		should_stop = philo->shared->stop_simulation;
		pthread_mutex_unlock(&philo->shared->stop_mutex);
		if (should_stop)
			break ;
		print_status(philo, "is sleeping");
		smart_sleep(philo->shared->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
