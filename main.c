/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/10/07 09:20:52 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void	create_philosophers_id(t_philo *philos, int num_of_philo,
		pthread_mutex_t *forks, char **args, int argc)
{
	int			i;
	long		start;

	i = 0;
	start = get_time();
	philos->env->start_time = start;
	philos->env->num_of_philo = num_of_philo;
	philos->env->time_to_die = ft_atol(args[2]) * 1000;
	philos->env->time_to_eat = ft_atol(args[3]) * 1000;
	philos->env->time_to_sleep = ft_atol(args[4]) * 1000;
	philos->env->is_running = 1;
	pthread_mutex_init(&philos->env->msg, NULL);
	while (i < num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].fork = forks;
		philos[i].last_meal_time = 0;
			// Convert to milliseconds
		philos[i].start_time = start;
		pthread_mutex_init(&philos[i].meal_lock, NULL); // Initialize mutex
		philos[i].is_eating = 0;
		philos[i].meals_finished = 0;
		// Optional argument: number_of_times_each_philosopher_must_eat
		if (argc == 6)
			philos->env->meals_required = ft_atol(args[5]) * 1000;
		else
			philos->env->meals_required = -1;
		i++;
	}
}

void	*monitor_philosophers(void *arg)
{
	t_philo	*philos;
	int		i;
	long	current_time;
	int		all_done;
	int		j;

	philos = (t_philo *)arg;
	j = 0;
	while (philos->env->is_running)
	{
		i = 0;
		all_done = 1;
		while (i < philos[0].total_philos)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
				// Lock before accessing last_meal_time or is_eating
			// Skip the death check if the philosopher is eating
			if (philos[i].is_eating == 0)
			{
				current_time = get_current_time(philos[i].start_time);
				// Check if the philosopher has exceeded time_to_die
				if ((current_time
						- philos[i].last_meal_time) > philos[i].time_to_die)
				{
					philos[i].is_running = 0;
					printf("%ld philosopher %d has died\n",
						get_current_time(philos[i].start_time), philos[i].id);
				}
				// Stop the simulation
			}
			if (!philos[0].is_running)
				break ;
			pthread_mutex_unlock(&philos[i].meal_lock); // Unlock after checking
			if (philos[i].meals_required != -1 && philos[i].meals_finished == 0)
			{
				all_done = 0;
			}
			i++;
		}
		// If all philosophers have eaten the required number of times,
		//stop the simulation
		if (all_done == 1 && philos[0].meals_required != -1)
		{
			j = 0;
			while (j <= philos[0].total_philos)
			{
				philos[j].is_running = 0;
				j++;
			}
			printf("All philosophers have eaten %d times. Simulation stopping...\n", philos[0].meals_required);
		}
		if (!philos[0].is_running)
		{
			return (NULL);
		}
		usleep(10); // Add a short dela   y to avoid excessive CPU usage
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	if (check_arguments(argc, argv) == 0)
	{
		return (0);
	}
	else
	{
		initiate_threads(argc, argv);
	}
	return (0);
}
