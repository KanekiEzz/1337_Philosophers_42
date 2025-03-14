/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:10:55 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/14 02:03:39 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	*meal_monitor(void *arg)
{
	t_philo	*philo;
	int		total_meals;

	total_meals = 0;
	philo = (t_philo *)arg;
	while (total_meals < philo->number_of_philosophers && philo->eat_count > 0)
	{
		sem_wait(philo->all_ate_sem);
		total_meals++;
	}
	if (total_meals == philo->number_of_philosophers)
		sem_post(philo->done_sem);
	return (NULL);
}

void cleanup_child_process(t_philosopher *philo)
{
	sem_close(philo->shared->forks_sem);
	sem_close(philo->shared->print_sem);
	sem_close(philo->shared->meal_check_sem);
	sem_close(philo->shared->done_sem);
	sem_close(philo->shared->all_ate_sem);
}

int create_philosopher_processes(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		philo->pids[i] = fork();
		if (philo->pids[i] == -1)
			return (1);
		else if (philo->pids[i] == 0)
		{
			philosopher_routine(&philo->philosophers[i]);
			cleanup_child_process(&philo->philosophers[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

int	start_meal_monitor(t_philo *philo)
{
	pthread_t	meal_thread;

	if (philo->eat_count > 0)
	{
		if (pthread_create(&meal_thread, NULL, meal_monitor, philo) != 0)
			return (1);
		pthread_detach(meal_thread);
	}
	return (0);
}

void stop_simulation(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (philo->pids[i] > 0)
		{
			kill(philo->pids[i], SIGTERM);
			waitpid(philo->pids[i], NULL, 0);
		}
		i++;
	}
}

int	start_simulation(t_philo *philo)
{
	philo->start_time = get_time();
	philo->stop_simulation = 0;
	if (initialize_philosophers(philo) != 0)
		return (1);
	if (create_philosopher_processes(philo) != 0)
		return (1);
	if (start_meal_monitor(philo) != 0)
		return (1);
	sem_wait(philo->done_sem);
	stop_simulation(philo);
	return (0);
}
