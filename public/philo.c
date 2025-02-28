/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:22:13 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/28 10:50:01 by iezzam           ###   ########.fr       */
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
        
        // Check if we should stop before proceeding
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
                
                // Use stop_mutex consistently
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
            // Use stop_mutex consistently
            pthread_mutex_lock(&philo->stop_mutex);
            philo->stop_simulation = 1;
            pthread_mutex_unlock(&philo->stop_mutex);
            return (NULL);
        }
        
        // usleep(1000);
        usleep(50);
    }
    return (NULL);
}
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
    
    // Initialize mutexes
    if (pthread_mutex_init(&philo->print_lock, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&philo->stop_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&philo->simulation_mutex, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&philo->shared_mutex, NULL) != 0)
        return (1);

    // Allocate memory for forks and philosophers
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->number_of_philosophers);
    if (!philo->forks)
        return (1);
    philo->philosophers = malloc(sizeof(t_philosopher) * philo->number_of_philosophers);
    if (!philo->philosophers)
    {
        free(philo->forks);
        return (1);
    }

    // Initialize forks
    i = 0;
    while (i < philo->number_of_philosophers)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
            return (1);
        i++;
    }

    // Initialize philosophers
    i = 0;
    while (i < philo->number_of_philosophers)
    {
        philo->philosophers[i].id = i + 1;
        philo->philosophers[i].meals_eaten = 0;
        philo->philosophers[i].last_meal_time = get_time();
        philo->philosophers[i].shared = philo;
        if (pthread_mutex_init(&philo->philosophers[i].meal_mutex, NULL) != 0)
            return (1);
            
        // Assign forks - handle circular assignment
        philo->philosophers[i].left_fork = &philo->forks[i];
        philo->philosophers[i].right_fork = &philo->forks[(i + 1) % philo->number_of_philosophers];

        // Create philosopher threads
        if (pthread_create(&philo->philosophers[i].thread, NULL, philosopher_routine, &philo->philosophers[i]) != 0)
            return (1);
        i++;
    }

    return (0);
}


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
    if (philo->shared->number_of_philosophers == 1)
    {
        smart_sleep(philo->shared->time_to_die);
        print_status(philo, "dided 💀");
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork 🍽️");

    pthread_mutex_lock(&philo->meal_mutex);
    print_status(philo, "is eating 🍝");
    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    smart_sleep(philo->shared->time_to_eat);

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

// void eat(t_philosopher *philo)
// {
//     pthread_mutex_lock(philo->left_fork);
//     print_status(philo, "has taken a fork 🍽️");
//     pthread_mutex_lock(philo->right_fork);
//     print_status(philo, "has taken a fork 🍽️");

//     print_status(philo, "is eating 🍝");
//     philo->last_meal_time = get_time();
//     philo->meals_eaten++;
//     smart_sleep(philo->shared->time_to_eat);

//     pthread_mutex_unlock(philo->right_fork);
//     pthread_mutex_unlock(philo->left_fork);
// }

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    int should_stop;

    // Avoid deadlocks by staggering the start times
    if (philo->id % 2 == 0)
        usleep(50);
        // usleep(100);

    while (1)
    {
        // Always check stop_simulation with mutex protection
        pthread_mutex_lock(&philo->shared->stop_mutex);
        should_stop = philo->shared->stop_simulation;
        pthread_mutex_unlock(&philo->shared->stop_mutex);

        if (should_stop)
            break;

        if (philo->shared->number_of_philosophers == 1)
        {
            eat(philo);
            return NULL;
        }

        eat(philo);
        print_status(philo, "is sleeping 😴");
        smart_sleep(philo->shared->time_to_sleep);
        print_status(philo, "is thinking 🤔");
    }
    return (NULL);
}

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

void smart_sleep(long long time)
{
    long long start;
    start = get_time();
    while ((get_time() - start) < time)
        usleep(50);
        // usleep(100);
    return ;
}

void print_status(t_philosopher *philo, char *msg)
{
    pthread_mutex_lock(&philo->shared->print_lock);
    if (!philo->shared->stop_simulation)
        printf("%lld %d %s\n", get_time() - philo->shared->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->shared->print_lock);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:38:30 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/30 13:22:48 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int parse_philo(int ac, char **av, t_philo *philo)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr("Usage: philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	philo->eat_count = -1;
	philo->number_of_philosophers = ft_atof(av[1]);
	philo->time_to_die = ft_atof(av[2]);
	philo->time_to_eat = ft_atof(av[3]);
	philo->time_to_sleep = ft_atof(av[4]);
	if (ac == 6)
		philo->eat_count = ft_atof(av[5]);
	if (philo->number_of_philosophers == 0.0 || philo->number_of_philosophers <= 0 || philo->time_to_die == 0.0 || philo->time_to_eat == 0.0 || philo->time_to_sleep == 0.0 || philo->eat_count == 0.0)
	{
		ft_putstr("Usage: philo [number_of_philosophers != 0 ] [time_to_die] [time_to_eat] [time_to_sleep] {number_of_times_each_philosopher_must_eat}\n");
		return (1);
	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	t_philo philo;

// 	if (parse_philo(ac, av, &philo) == 1)
// 		return 0;
// 	fprintf(stderr, "number_of_philosophers: %d\n", philo.number_of_philosophers);
// 	fprintf(stderr, "time_to_die: %d\n", philo.time_to_die);
// 	fprintf(stderr, "time_to_eat: %d\n", philo.time_to_eat);
// 	fprintf(stderr, "time_to_sleep: %d\n", philo.time_to_sleep);
// 	fprintf(stderr, "eat_count: %d\n", philo.eat_count);
// 	// philo_init(&philo);
// 	return 0;
// }
void philo_cleanup(t_philo *philo)
{
    int i;

    // Wait for all philosopher threads to finish
    i = 0;
    while (i < philo->number_of_philosophers)
        pthread_join(philo->philosophers[i++].thread, NULL);

    // Destroy all mutexes
    i = 0;
    while (i < philo->number_of_philosophers)
    {
        pthread_mutex_destroy(&philo->forks[i]);
        pthread_mutex_destroy(&philo->philosophers[i].meal_mutex);
        i++;
    }

    // Destroy global mutexes
    pthread_mutex_destroy(&philo->print_lock);
    pthread_mutex_destroy(&philo->stop_mutex);
    pthread_mutex_destroy(&philo->simulation_mutex);
    pthread_mutex_destroy(&philo->shared_mutex);

    // Free allocated memory
    free(philo->forks);
    free(philo->philosophers);
}

// Fix main function to use the cleanup function properly
int main(int ac, char **av)
{
    t_philo philo;
    pthread_t monitor;

    if (parse_philo(ac, av, &philo))
        return (1);
    if (philo_init(&philo))
        return (1);

    if (philo.number_of_philosophers == 1)
    {
        // Handle special case for 1 philosopher
        philo_cleanup(&philo);
    }
    else
    {
        // Create monitor thread and wait for it
        if (pthread_create(&monitor, NULL, monitor_routine, &philo) != 0)
        {
            philo_cleanup(&philo);
            return (1);
        }

        pthread_join(monitor, NULL);

        // Clean up resources
        philo_cleanup(&philo);
    }

    return (0);
}
