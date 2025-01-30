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

    while (!philo->stop_simulation)
    {
        i = 0;
        while (i < philo->number_of_philosophers)
        {
            if (get_time() - philo->philosophers[i].last_meal_time > philo->time_to_die)
            {
                print_status(&philo->philosophers[i], "died");
                philo->stop_simulation = 1;
                break;
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}
