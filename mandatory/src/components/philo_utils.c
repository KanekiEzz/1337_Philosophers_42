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



/* This function returns the current time in milliseconds.*/
// ou
// tv.tv_sec * 1000 converts seconds to milliseconds
// tv.tv_usec / 1000 converts microseconds to milliseconds.
long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
// size_t	time_now(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		write(2, "gettimeofday() error\n", 22);
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }

void smart_sleep(long long time)
{
    long long start;
    start = get_time();
    while ((get_time() - start) < time)
        usleep(100);
    return ;
}

void print_status(t_philosopher *philo, char *msg)
{
    pthread_mutex_lock(&philo->shared->print_lock);
    if (!philo->shared->stop_simulation)
        printf("%lld %d %s\n", get_time() - philo->shared->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->shared->print_lock);
}
