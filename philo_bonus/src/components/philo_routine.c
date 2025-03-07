/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/07 09:00:56 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void print_status(t_philo *philo, char *msg)
{
	sem_wait(philo->data->print);
	printf("%lld %d %s\n", get_time() - philo->data->start_time, philo->id + 1, msg);
	sem_post(philo->data->print);
}

void eat(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");

	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);

	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void *monitor(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		if ((get_time() - philo->last_meal) > philo->data->time_to_die)
		{
			print_status(philo, "died");
			sem_post(philo->data->stop);
			exit(1);
		}
		usleep(1000);
	}
}

void philo_process(t_philo *philo)
{
	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_detach(monitor_thread);

	while (1)
	{
		eat(philo);
		if (philo->data->num_meals != -1 && philo->meals_eaten >= philo->data->num_meals)
			exit(0);
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	exit(0);
}

void start_simulation(t_data *data)
{
	int i;
	int status;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			philo_process(&data->philos[i]);
		i++;
	}
	if (data->num_meals != -1)
	{
		i = 0;
		while (i < data->num_philos)
			waitpid(data->philos[i++].pid, &status, 0);
	}
	else
	{
		i = 0;
		sem_wait(data->stop);
		while (i < data->num_philos)
			kill(data->philos[i++].pid, SIGTERM);
	}
}

void cleanup(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->stop);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/stop");
	free(data->philos);
}
