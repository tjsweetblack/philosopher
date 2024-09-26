/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/09/26 19:34:37 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

long	get_time()
{
	struct timeval time;
	gettimeofday(&time, 0);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000)); 	
}

long	get_current_time(long start)
{
	return(get_time() - start);
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
        ft_printf("%s", "running\n");
    }
    else
    {
        ft_printf("%s", "num of args");
        exit(0);
    }
    return ;
}

void create_philosophers_id(t_philo *philos, int num_of_philo,  pthread_mutex_t *forks)
{
    int i;
    
    i = 0;
    while (i < num_of_philo)
    {
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].total_philos = num_of_philo;
	philos[i].fork = forks;
        i++;
    }
    return ;
}

void ft_sleep(t_philo philo, long start)
{
    printf("%ld philosopher %d is slepping\n", get_current_time(start) , philo.id);
    usleep(200 * 1000);
}

void ft_right_fork(t_philo philo, pthread_mutex_t *forks, long start)
{
    pthread_mutex_lock(&forks[(philo.id - 1)]);
    printf("%ld philosopher %d held the right fork\n", get_current_time(start), philo.id);
}

void ft_left_fork(t_philo philo, pthread_mutex_t *forks, long start)
{
    pthread_mutex_lock(&forks[(philo.id  % philo.total_philos)]);
    printf("%ld philosopher %d held the left fork\n", get_current_time(start), philo.id);
}

void ft_eat(t_philo philo, pthread_mutex_t *forks, long start)
{
    ft_right_fork(philo, forks, start);
    ft_left_fork(philo, forks, start);
    printf("%ld philosopher %d is eating\n", get_current_time(start), philo.id);
    usleep(200 * 1000);
    printf("%ld philosopher %d left the right fork\n", get_current_time(start), philo.id);
    pthread_mutex_unlock(&forks[(philo.id - 1)]);
    printf("%ld philosopher %d left the left fork\n", get_current_time(start), philo.id);
    pthread_mutex_unlock(&forks[(philo.id  % philo.total_philos)]);
    
}

void ft_think(t_philo philo, long start)
{
    printf("%ld philosopher %d is thinking\n", get_current_time(start), philo.id);
}

void *philosopher_process(void *arg)
{
    t_philo philo = *((t_philo *)arg);
    long	 start;

    start = get_time();
    while (1)
    {
        ft_think(philo, start); 
        ft_eat(philo, philo.fork, start);
        ft_sleep(philo, start);  
    }
    free(arg);
    return NULL;
}


void main_porcess(char **argv)
{
    int num_of_philo;
    t_philo *philos;
    pthread_t *threads;
    int j;
    int k;
    int l;

    j = 0;
    k = 0;
    l = 0;
    num_of_philo = atoi(argv[1]);
    philos = malloc(sizeof(t_philo) * num_of_philo);
    threads = malloc(sizeof(pthread_t) * num_of_philo);
    pthread_mutex_t *forks;
    forks = malloc(sizeof(pthread_mutex_t) * num_of_philo);

    while (l < num_of_philo)
    {
        pthread_mutex_init(&forks[l], NULL);
	l++;
    }
    create_philosophers_id(philos, num_of_philo, forks);
    while (j < num_of_philo)
    {
        pthread_create(&threads[j], NULL, philosopher_process, &philos[j]);
        j++;
    }
    while (k < num_of_philo)
    {
        pthread_join(threads[k], NULL);
        k++;
    }

    // Use the array of philosophers as needed
    // ...

    // Don't forget to free the allocated memory when you're done
    free(philos);
    free(threads);
}
int main(int argc, char **argv)
{
    check_arguments(argc, argv);
    main_porcess(argv);
    //printf("%ld", get_current_time());
    return(0);
}
