/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:19:50 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/28 23:01:39 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

/* This function returns the current time in milliseconds.*/
// ou
// tv.tv_sec * 1000 converts seconds to milliseconds
// tv.tv_usec / 1000 converts microseconds to milliseconds.
long	long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	smart_sleep(long long time)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
	return ;
}

void	print_status(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared->print_lock);
	pthread_mutex_lock(&philo->shared->stop_mutex);
	if (!philo->shared->stop_simulation)
		printf("%lld %d %s\n", get_time() - philo->shared->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->shared->stop_mutex);
	pthread_mutex_unlock(&philo->shared->print_lock);
}
