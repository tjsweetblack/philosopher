/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/10/12 23:12:35 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

void	store_to_struct(t_philo *philos, int num_of_philo,
		pthread_mutex_t *forks, char **args, int argc)
{
	int		i;
	long	start;
	t_env	*env;

	i = 0;
	start = get_time();
	env = malloc(sizeof(t_env));
	if (env == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	env->start_time = start;
	env->num_of_philo = num_of_philo;
	env->time_to_die = ft_atol(args[2]);
	env->time_to_eat = ft_atol(args[3]) * 1000;
	env->time_to_sleep = ft_atol(args[4]) * 1000;
	env->is_running = 1;
	env->fork = forks;
	pthread_mutex_init(&env->msg, NULL);
	if (argc == 6)
		env->meals_required = ft_atol(args[5]);
	else
		env->meals_required = -1;
	while (i < num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal_time = get_time();
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		philos[i].is_eating = 0;
		philos[i].meals_finished = 0;
		philos[i].env = env;
		printf("%d\n", philos[i].id);
		i++;
	}
}

void	*monitor_philosophers(void *arg)
{
	t_philo	*philos;
	int		i;
	long	current_time;
	int		all_done;

	philos = (t_philo *)arg;
	while (philos->env->is_running)
	{
		i = 0;
		all_done = 1;
		while (i < philos->env->num_of_philo)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			// Lock before accessing last_meal_time or is_eating
			// Skip the death check if the philosopher is eating
			if (philos[i].is_eating == 0)
			{
				current_time = get_current_time(philos[i].env->start_time);
				// Check if the philosopher has exceeded time_to_die
				if ((current_time
						- philos[i].last_meal_time) > philos[i].env->time_to_die)
				{
					philos->env->is_running = 0;
					printf("%ld philosopher %d has died\n",
						get_current_time(philos[i].env->start_time),
						philos[i].id);
				}
				// Stop the simulation
			}
			if (!philos->env->is_running)
				break ;
			pthread_mutex_unlock(&philos[i].meal_lock); // Unlock after checking
			if (philos->env->meals_required != -1
				&& philos[i].meals_finished == 0)
			{
				all_done = 0;
			}
			i++;
		}
		// If all philosophers have eaten the required number of times,
		// stop the simulation
		if (all_done == 1 && philos->env->meals_required != -1)
		{
			philos->env->is_running = 0;
			printf("All philosophers have eaten");
			printf("%d times. Simulation stopping...\n",
				philos->env->meals_required);
		}
		if (!philos->env->is_running)
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
