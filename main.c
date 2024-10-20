/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/10/19 23:53:22 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

void store_to_struct(t_philo *philos, int num_of_philo, pthread_mutex_t *forks, char **args, int argc)
{
    int i;
    long start;
    t_env *env;

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
	env->fork = forks;
    env->time_to_sleep = ft_atol(args[4]) * 1000;
    env->is_running = 1;
    env->cycle_count = 0;
    pthread_mutex_init(&env->msg, NULL);
    pthread_mutex_init(&env->meal_lock, NULL);

    if (argc == 6)
        env->meals_required = ft_atol(args[5]);
    else
        env->meals_required = -1;

    env->total_times_eaten = 0;

    while (i < num_of_philo)
    {
        philos[i].id = i + 1;
        philos[i].last_meal_time = get_current_time(env->start_time);
        philos[i].is_eating = 0;
        philos[i].meals_finished = 0;
        philos[i].cycle_flag = 0;
        philos[i].env = env;
        i++;
    }
}

void check_philo_time_to_die(t_philo *philo)
{
	long current_time;
	current_time = get_current_time(philo->env->start_time);
	if (current_time - philo->last_meal_time > philo->env->time_to_die)
	{
		philo->env->is_running = 0;
		print_philo_message("DIED", *philo);
	}
}

void check_all_eaten(t_philo *philos)
{
   if(philos->env->total_times_eaten == (philos->env->num_of_philo * philos->env->meals_required))
   {
       philos->env->is_running = 0;
       print_philo_message("DIED", philos[0]);
   }
}

void *ft_monitoring(void *args)
{
    t_philo *philos;
    int i;
    int all_done;
    int num_of_philo;

    philos = (t_philo *)args;
    num_of_philo = philos->env->num_of_philo;

    while (philos->env->is_running)
    {
        i = 0;
        all_done = 1; // Reset all_done at the beginning of each loop

        while (i < num_of_philo && philos->env->is_running)
        {
            check_philo_time_to_die(&philos[i]);
            i++;
        }

        check_all_eaten(philos);

        if (all_done)
        {
            // If all philosophers have eaten the required number of meals, stop the simulation
            philos->env->is_running = 0;
        }
    }

    return (NULL);
}


int main(int argc, char **argv)
{
    check_arguments(argc, argv);
    initiate_threads(argc, argv);
    return 0;
}