/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/09/27 08:32:37 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

#include "./includes/philosopher.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

long get_time()
{
    struct timeval time;
    gettimeofday(&time, 0);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); 
}

long get_current_time(long start)
{
    // Get current time in milliseconds and subtract the start time
    return get_time() - start;
}

void check_arguments_int(char **argv)
{
    int i;
    int j;
    int digit;

    i = 1;
    while (argv[i])
    {
        j = 0;
        while (argv[i][j])
        {
            digit = ft_isdigit(argv[i][j]);
            if(digit == 0)
            {
                printf("%s", "Error\n not a digit");
                exit(0);
            }
            j++;
        }
        i++;
    }
}

void check_arguments(int argc, char **argv)
{
    if (argc == 5)
    {
        check_arguments_int(argv);
        printf("%s", "running\n");
    }
    else
    {
        printf("%s", "num of args");
        exit(0);
    }
}

void create_philosophers_id(t_philo *philos, int num_of_philo, pthread_mutex_t *forks, char **args)
{
    int i;
    long start;

    i = 0;
    start = get_time();
    while (i < num_of_philo)
    {
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].total_philos = num_of_philo;
        philos[i].fork = forks;
        philos[i].last_meal_time = 0;
        philos[i].time_to_die = atol(args[2]) * 1; // Convert to milliseconds
        philos[i].start_time = start;
        philos[i].time_to_eat = atol(args[3]);
        pthread_mutex_init(&philos[i].meal_lock, NULL); // Initialize mutex
        philos[i].is_eating = 0;
        philos[i].time_to_sleep = atol(args[4]) * 1000;
        i++;
    }
}

void ft_sleep(t_philo philo)
{
    printf("%ld philosopher %d is sleeping\n", get_current_time(philo.start_time), philo.id);
    usleep(philo.time_to_sleep); // Sleep for 200ms
}

void ft_right_fork(t_philo philo, pthread_mutex_t *forks)
{
    pthread_mutex_lock(&forks[philo.id - 1]);
    printf("%ld philosopher %d held the right fork\n", get_current_time(philo.start_time), philo.id);
}

void ft_left_fork(t_philo philo, pthread_mutex_t *forks)
{
    pthread_mutex_lock(&forks[philo.id % philo.total_philos]);
    printf("%ld philosopher %d held the left fork\n", get_current_time(philo.start_time), philo.id);
}

void ft_eat(t_philo *philo, pthread_mutex_t *forks)
{
    ft_right_fork(*philo, forks);
    ft_left_fork(*philo, forks);

    pthread_mutex_lock(&philo->meal_lock); // Lock access to last_meal_time
    philo->last_meal_time = get_current_time(philo->start_time);
    philo->is_eating = 1; // Mark philosopher as eating
    pthread_mutex_unlock(&philo->meal_lock); // Unlock access

    printf("%ld philosopher %d is eating\n", get_current_time(philo->start_time), philo->id);

    usleep(philo->time_to_eat); // Eating for 200ms

    pthread_mutex_lock(&philo->meal_lock); // Lock access again before changing the state
    philo->is_eating = 0; // Mark philosopher as done eating
    pthread_mutex_unlock(&philo->meal_lock); // Unlock access

    printf("%ld philosopher %d left the right fork\n", get_current_time(philo->start_time), philo->id);
    pthread_mutex_unlock(&forks[philo->id - 1]);

    printf("%ld philosopher %d left the left fork\n", get_current_time(philo->start_time), philo->id);
    pthread_mutex_unlock(&forks[philo->id % philo->total_philos]);
}

void ft_think(t_philo philo)
{
    printf("%ld philosopher %d is thinking\n", get_current_time(philo.start_time), philo.id);
}

void *philosopher_process(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (1)
    {
        ft_think(*philo);
        ft_eat(philo, philo->fork);
        ft_sleep(*philo);
    }
    return NULL;
}

void *monitor_philosophers(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    int i;
    long current_time;

    while (1)
    {
        i = 0;
        while (i < philos[0].total_philos)
        {
            pthread_mutex_lock(&philos[i].meal_lock); // Lock before accessing last_meal_time or is_eating
            
            // Skip the death check if the philosopher is eating
            if (philos[i].is_eating == 0)
            {
                current_time = get_current_time(philos[i].start_time);
                // Check if the philosopher has exceeded time_to_die
                if ((current_time - philos[i].last_meal_time) > philos[i].time_to_die)
                {
                    printf("%ld philosopher %d has died\n", get_current_time(philos[i].start_time), philos[i].id);
                    exit(0); // Exit the program if a philosopher dies
                }
            }
            
            pthread_mutex_unlock(&philos[i].meal_lock); // Unlock after checking
            i++;
        }
        usleep(1000); // Add a short delay to avoid excessive CPU usage
    }
    return NULL;
}

void main_process(char **argv)
{
    int num_of_philo;
    t_philo *philos;
    pthread_t *threads;
    pthread_t monitor;
    pthread_mutex_t *forks;
    int i;

    num_of_philo = atoi(argv[1]);
    philos = malloc(sizeof(t_philo) * num_of_philo);
    threads = malloc(sizeof(pthread_t) * num_of_philo);
    forks = malloc(sizeof(pthread_mutex_t) * num_of_philo);

    for (i = 0; i < num_of_philo; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    create_philosophers_id(philos, num_of_philo, forks, argv);

    for (i = 0; i < num_of_philo; i++)
    {
        pthread_create(&threads[i], NULL, philosopher_process, &philos[i]);
    }

    pthread_create(&monitor, NULL, monitor_philosophers, philos);

    for (i = 0; i < num_of_philo; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(philos);
    free(threads);
    free(forks);
}

int main(int argc, char **argv)
{
    check_arguments(argc, argv);
    main_process(argv);
    return 0;
}

