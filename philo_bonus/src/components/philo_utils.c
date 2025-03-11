/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:19:50 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/11 23:04:01 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

long long	get_time(void)
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
	sem_wait(philo->shared->print_sem);
	printf("%lld %d %s\n", get_time() - \
		philo->shared->start_time, philo->id, msg);
	if (ft_strcmp(msg, "died") != 0)
		sem_post(philo->shared->print_sem);
	else
		sem_post(philo->shared->done_sem);
}
