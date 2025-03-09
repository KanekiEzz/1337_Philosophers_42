/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:38:30 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/09 01:46:16 by iezzam           ###   ########.fr       */
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

void philo_cleanup(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (philo->pids[i] > 0)
			kill(philo->pids[i], SIGKILL);
		i++;
	}

	close_semaphores(philo);

	if (philo->philosophers)
		free(philo->philosophers);
	if (philo->pids)
		free(philo->pids);
}

void *meal_monitor(void *arg)
{
	t_philo *philo;
	int total_meals = 0;

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

int	initialize_philosophers(t_philo *philo)
{
	int i;

	i = 0;
	while (i< philo->number_of_philosophers)
	{
		philo->philosophers[i].id = i + 1;
		philo->philosophers[i].meals_eaten = 0;
		philo->philosophers[i].last_meal_time = get_time();
		philo->philosophers[i].shared = philo;
		i++;
	}
	return (0);
}

int	create_philosopher_processes(t_philo *philo)
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
			exit(0);
		}
		i++;
	}
	return (0);
}

int start_meal_monitor(t_philo *philo)
{
	pthread_t meal_thread;

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
			kill(philo->pids[i], SIGTERM);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}
int start_simulation(t_philo *philo)
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

// int start_simulation(t_philo *philo)
// {
// 	int i;
// 	pthread_t meal_thread;

// 	philo->start_time = get_time();
// 	philo->stop_simulation = 0;
// 	i = 0;
// 	while (i < philo->number_of_philosophers)
// 	{
// 		philo->philosophers[i].id = i + 1;
// 		philo->philosophers[i].meals_eaten = 0;
// 		philo->philosophers[i].last_meal_time = get_time();
// 		philo->philosophers[i].shared = philo;

// 		philo->pids[i] = fork();
// 		if (philo->pids[i] == -1)
// 			return (1);
// 		else if (philo->pids[i] == 0)
// 		{
// 			philosopher_routine(&philo->philosophers[i]);
// 			exit(0);
// 		}
// 		i++;
// 	}
// 	if (philo->eat_count > 0)
// 	{
// 		if (pthread_create(&meal_thread, NULL, meal_monitor, philo) != 0)
// 			return (1);
// 		pthread_detach(meal_thread);
// 	}
// 	sem_wait(philo->done_sem);
// 	i = 0;
// 	while (i < philo->number_of_philosophers)
// 	{
// 		if (philo->pids[i] > 0)
// 			kill(philo->pids[i], SIGTERM);
// 		i++;
// 	}
// 	while (waitpid(-1, NULL, 0) > 0)
// 		;
// 	return (0);
// }

int main(int ac, char **av)
{
	t_philo philo;

	if (parse_philo(ac, av, &philo))
		return (1);
	if (philo_init(&philo))
		return (1);

	if (start_simulation(&philo))
	{
		philo_cleanup(&philo);
		return (1);
	}

	philo_cleanup(&philo);
	return (0);
}
