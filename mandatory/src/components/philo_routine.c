/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:20:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/30 13:21:15 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"



void eat(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, "has taken a fork 🍽️");
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork 🍽️");

    print_status(philo, "is eating 🍝");
    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    smart_sleep(philo->shared->time_to_eat);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

    if (philo->id % 2 == 0) // Avoid deadlock by staggering even philosophers
        usleep(100);

    while (!philo->shared->stop_simulation)
    {
        print_status(philo, "is thinking 🤔");
        eat(philo);
        print_status(philo, "is sleeping 😴");
        smart_sleep(philo->shared->time_to_sleep);
    }
    return (NULL);
}
