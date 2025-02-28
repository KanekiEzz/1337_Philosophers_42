/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:22:13 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/30 13:39:12 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void *monitor_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int i;
    long long x_time;
    int philosophers_done_eating;

    while (1)
    {
        i = 0;
        philosophers_done_eating = 0;
        pthread_mutex_lock(&philo->stop_mutex);
        if (philo->stop_simulation)
        {
            pthread_mutex_unlock(&philo->stop_mutex);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->stop_mutex);
        while (i < philo->number_of_philosophers)
        {
            pthread_mutex_lock(&philo->philosophers[i].meal_mutex);
            x_time = get_time() - philo->philosophers[i].last_meal_time;   
            if (x_time > philo->time_to_die)
            {
                print_status(&philo->philosophers[i], "died 💀");
                
                pthread_mutex_lock(&philo->stop_mutex);
                philo->stop_simulation = 1;
                pthread_mutex_unlock(&philo->stop_mutex);
                
                pthread_mutex_unlock(&philo->philosophers[i].meal_mutex);
                return (NULL);
            }
            if (philo->eat_count > 0 && philo->philosophers[i].meals_eaten >= philo->eat_count)
                philosophers_done_eating++;
            pthread_mutex_unlock(&philo->philosophers[i].meal_mutex);
            i++;
        }
        if (philo->eat_count > 0 && philosophers_done_eating == philo->number_of_philosophers)
        {
            pthread_mutex_lock(&philo->stop_mutex);
            philo->stop_simulation = 1;
            pthread_mutex_unlock(&philo->stop_mutex);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}
