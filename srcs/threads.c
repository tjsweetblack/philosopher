/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 07:09:45 by badriano          #+#    #+#             */
/*   Updated: 2024/10/12 23:32:28 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void    free_all(t_philo *philos, int num_of_philo, pthread_t *threads,
    pthread_mutex_t *forks)
{
    int i;

    i = 0;
    while (i < num_of_philo)
    {
        pthread_mutex_destroy(&forks[i]);
        pthread_mutex_destroy(&philos[i].meal_lock);
        i++;
    }
    pthread_mutex_destroy(&philos->env->msg);
	free(philos);
	free(threads);
	free(forks);
}
void create_philosofer_thread(int num_of_philo, t_philo *philos,
        pthread_t *threads)
{
        int i;

        i = 0;
        while(i < num_of_philo)
        {
            pthread_create(&threads[i], NULL, philosopher_process, &philos[i]);
            i++;
        }

}
void join_threads(pthread_t *threads, int num_of_philo)
{
        int i;
        
        i = 0;
        while(i < num_of_philo)
        {
            pthread_join(threads[i], NULL);
            i++;
        }
}
void init_mutexts(int num_of_philo, pthread_mutex_t *forks)
{
        int i;
        
        i = 0;
        while(i < num_of_philo)
        {
            pthread_mutex_init(&forks[i], NULL);
            i++;
        }
}

void	initiate_threads(int argc, char **argv)
{
	int				num_of_philo;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_t		monitor;
	pthread_mutex_t	*forks;

	num_of_philo = atoi(argv[1]);
	philos = malloc(sizeof(t_philo) * num_of_philo);
	threads = malloc(sizeof(pthread_t) * num_of_philo);
	forks = malloc(sizeof(pthread_mutex_t) * num_of_philo);
    	init_mutexts(num_of_philo, forks);
	store_to_struct(philos, num_of_philo, forks, argv, argc);
    	create_philosofer_thread(num_of_philo, philos, threads);
	pthread_create(&monitor, NULL, monitor_philosophers, philos);
    	join_threads(threads, num_of_philo);
    	free_all(philos, num_of_philo, threads, forks);
}
