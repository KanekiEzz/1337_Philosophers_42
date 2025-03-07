/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:21:41 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/07 09:05:24 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void init_data(t_data *data, int argc, char **argv)
{
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->num_meals = (argc == 6) ? atoi(argv[5]) : -1;
    data->start_time = get_time();

    sem_unlink("/forks");
    sem_unlink("/print");
    sem_unlink("/stop");
    
    data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
    data->print = sem_open("/print", O_CREAT, 0644, 1);
    data->stop = sem_open("/stop", O_CREAT, 0644, 0);
    
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
}

void init_philos(t_data *data)
{
	int	i;

	i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = get_time();
        data->philos[i].data = data;
		i++;
    }
}
