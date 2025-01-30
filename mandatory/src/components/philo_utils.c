/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:19:50 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/30 13:21:18 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"



// Get current timestamp in milliseconds
long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// Smart sleep function to prevent CPU overuse
void smart_sleep(long long time)
{
    long long start = get_time();
    while ((get_time() - start) < time)
        usleep(100);
}

// Print function with mutex to avoid mixed output
void print_status(t_philosopher *philo, char *msg)
{
    pthread_mutex_lock(&philo->shared->print_lock);
    if (!philo->shared->stop_simulation)
        printf("%lld %d %s\n", get_time() - philo->shared->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->shared->print_lock);
}
