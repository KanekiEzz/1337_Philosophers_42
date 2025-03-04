/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:38:30 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/04 12:21:52 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parse_philo(int ac, char **av, t_philo *philo)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr("Usage: philo number_of_philosophers\
			time_to_die time_to_eat time_to_sleep \
			[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	philo->eat_count = -1;
	philo->number_of_philosophers = ft_atof(av[1]);
	philo->time_to_die = ft_atof(av[2]);
	philo->time_to_eat = ft_atof(av[3]);
	philo->time_to_sleep = ft_atof(av[4]);
	if (ac == 6)
		philo->eat_count = ft_atof(av[5]);
	if (philo->number_of_philosophers == 0.0
		|| philo->number_of_philosophers <= 0
		|| philo->time_to_die == 0.0 || philo->time_to_eat == 0.0
		|| philo->time_to_sleep == 0.0 || philo->eat_count == 0.0)
	{
		ft_putstr("Usage: philo [number_of_philosophers != 0 ] \
			[time_to_die] [time_to_eat] [time_to_sleep] \
			{number_of_times_each_philosopher_must_eat}\n");
		return (1);
	}
	return (0);
}

void	philo_cleanup(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
		pthread_join(philo->philosophers[i++].thread, NULL);
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		pthread_mutex_destroy(&philo->philosophers[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&philo->print_lock);
	pthread_mutex_destroy(&philo->stop_mutex);
	pthread_mutex_destroy(&philo->shared_mutex);
	free(philo->forks);
	free(philo->philosophers);
}

int	main(int ac, char **av)
{
	t_philo		philo;
	pthread_t	monitor;

	if (parse_philo(ac, av, &philo))
		return (1);
	if (philo_init(&philo))
		return (1);
	if (philo.number_of_philosophers == 1)
		philo_cleanup(&philo);
	else
	{
		if (pthread_create(&monitor, NULL, monitor_routine, &philo) != 0)
		{
			philo_cleanup(&philo);
			return (1);
		}
		pthread_join(monitor, NULL);
		philo_cleanup(&philo);
	}
	return (0);
}
