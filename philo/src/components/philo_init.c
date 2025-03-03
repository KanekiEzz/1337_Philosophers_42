/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:21:41 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/28 22:55:37 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	init(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->number_of_philosophers)
	{
		if (pthread_mutex_init(&philo->forks[i++], NULL) != 0)
			return (1);
	}
	i = -1;
	while (++i < philo->number_of_philosophers)
	{
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].meals_eaten = 0;
		philo->philosophers[i].last_meal_time = get_time();
		philo->philosophers[i].shared = philo;
		if (pthread_mutex_init(&philo->philosophers[i].meal_mutex, NULL) != 0)
			return (1);
		philo->philosophers[i].left_fork = &philo->forks[i];
		philo->philosophers[i].right_fork
			= &philo->forks[(i + 1) % philo->number_of_philosophers];
		if (pthread_create(&philo->philosophers[i].thread, NULL, \
				philosopher_routine, &philo->philosophers[i]) != 0)
			return (1);
	}
	return (0);
}

int	philo_init(t_philo *philo)
{
	philo->stop_simulation = 0;
	philo->start_time = get_time();
	if (pthread_mutex_init(&philo->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->stop_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->simulation_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->shared_mutex, NULL) != 0)
		return (1);
	philo->forks = malloc(sizeof(pthread_mutex_t)
			* philo->number_of_philosophers);
	if (!philo->forks)
		return (1);
	philo->philosophers = malloc(sizeof(t_philosopher)
			* philo->number_of_philosophers);
	if (!philo->philosophers)
	{
		free(philo->forks);
		return (1);
	}
	init(philo);
	return (0);
}
