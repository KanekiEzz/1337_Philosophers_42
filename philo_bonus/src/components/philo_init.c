/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:21:41 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/08 17:57:48 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void    create_semaphores(t_philo *philo)
{
    sem_unlink("forks");
    sem_unlink("print");
    sem_unlink("meal_check");
    sem_unlink("done");
    sem_unlink("all_ate");

    philo->forks_sem = sem_open("forks", O_CREAT, 0644, philo->number_of_philosophers);
    philo->print_sem = sem_open("print", O_CREAT, 0644, 1);
    philo->meal_check_sem = sem_open("meal_check", O_CREAT, 0644, 1);
    philo->done_sem = sem_open("done", O_CREAT, 0644, 0);
    philo->all_ate_sem = sem_open("all_ate", O_CREAT, 0644, 0);
}

void    close_semaphores(t_philo *philo)
{
    sem_close(philo->forks_sem);
    sem_close(philo->print_sem);
    sem_close(philo->meal_check_sem);
    sem_close(philo->done_sem);
    sem_close(philo->all_ate_sem);

    sem_unlink("forks");
    sem_unlink("print");
    sem_unlink("meal_check");
    sem_unlink("done");
    sem_unlink("all_ate");
}

int    philo_init(t_philo *philo)
{
    philo->stop_simulation = 0;
    philo->start_time = get_time();

    create_semaphores(philo);

    philo->philosophers = malloc(sizeof(t_philosopher) * philo->number_of_philosophers);
    if (!philo->philosophers)
        return (1);
    
    philo->pids = malloc(sizeof(pid_t) * philo->number_of_philosophers);
    if (!philo->pids)
    {
        free(philo->philosophers);
        return (1);
    }

    return (0);
}