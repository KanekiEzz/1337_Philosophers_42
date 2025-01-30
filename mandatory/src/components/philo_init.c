/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:21:41 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/30 13:36:02 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"


int philo_init(t_philo *philo)
{
    int i;

    philo->stop_simulation = 0;
    philo->start_time = get_time();
    pthread_mutex_init(&philo->print_lock, NULL);

    // Allocate philosophers and forks
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_of_philosophers);
    philo->philosophers = malloc(sizeof(t_philosopher) * philo->number_of_philosophers);
    if (!philo->forks || !philo->philosophers)
        return (1);


    i = 0;
    while (i < philo->number_of_philosophers)
        pthread_mutex_init(&philo->forks[i++], NULL);

    // Initialize philosopher data
    i = 0;
    while (i < philo->number_of_philosophers)
    {
        philo->philosophers[i].id = i + 1;
        philo->philosophers[i].meals_eaten = 0;
        philo->philosophers[i].last_meal_time = get_time();
        philo->philosophers[i].left_fork = &philo->forks[i];
        philo->philosophers[i].right_fork = &philo->forks[(i + 1) % philo->number_of_philosophers];
        philo->philosophers[i].shared = philo;
        i++;
    }

    i = 0;
    // Create philosopher threads
    while (i < philo->number_of_philosophers)
    {
        pthread_create(&philo->philosophers[i].thread, NULL, philosopher_routine, &philo->philosophers[i]);
        i++;
    }

    return (0);
}
