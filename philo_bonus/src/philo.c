/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:38:30 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/07 09:04:24 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int parse_philo(int ac, char **av, t_data *philo)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr("Usage: philo number_of_philosophers\
			time_to_die time_to_eat time_to_sleep \
			[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	philo->num_meals = -1;
	philo->num_philos = ft_atof(av[1]);
	philo->time_to_die = ft_atof(av[2]);
	philo->time_to_eat = ft_atof(av[3]);
	philo->time_to_sleep = ft_atof(av[4]);
	if (ac == 6)
		philo->num_meals = ft_atof(av[5]);
	if (philo->num_philos == 0.0 || philo->num_philos <= 0 || philo->time_to_die == 0.0 || philo->time_to_eat == 0.0 || philo->time_to_sleep == 0.0 || philo->num_meals == 0.0)
	{
		ft_putstr("Usage: philo [number_of_philosophers != 0 ] \
			[time_to_die] [time_to_eat] [time_to_sleep] \
			{number_of_times_each_philosopher_must_eat}\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data data;

	if (parse_philo(ac, av, &data))
		return (1);
	init_data(&data, ac, av);
	init_philos(&data);
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
