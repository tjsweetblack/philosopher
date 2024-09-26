/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/09/19 13:06:44 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

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
void create_philosophers_id(t_philo *philos, int num_of_philo)
{
    int i;
    
    i = 0;
    while (i < num_of_philo)
    {
        philos[i].id = i + 1;
        philos[i].eat_count = 0;
        philos[i].total_philos = num_of_philo;
        i++;
    }
    return ;
}
void ft_sleep(t_philo philo)
{
    printf("philosopher %d is slepping\n", philo.id);
    usleep(200 * 1000);
}
void ft_right_fork(t_philo philo, pthread_mutex_t *forks)
{
    pthread_mutex_lock(&forks[(philo.id - 1)]);
    printf("philosopher %d held the right fork\n", philo.id);
}
void ft_left_fork(t_philo philo, pthread_mutex_t *forks)
{
    pthread_mutex_lock(&forks[(philo.id  % philo.total_philos)]);
    printf("philosopher %d held the left fork\n", philo.id);
}
void ft_eat(t_philo philo, pthread_mutex_t *forks)
{
    ft_right_fork(philo, forks);
    ft_left_fork(philo, forks);
    printf("philosopher %d is eating\n", philo.id);
    usleep(200 * 1000);
    printf("philosopher %d left the right fork\n", philo.id);
    pthread_mutex_unlock(&forks[(philo.id - 1)]);
    printf("philosopher %d left the left fork\n", philo.id);
    pthread_mutex_unlock(&forks[(philo.id  % philo.total_philos)]);
    
}
void ft_think(t_philo philo)
{
    printf("philosopher %d is thinking\n", philo.id);
}
void *philosopher_process(void *arg)
{
    t_philo philo = *((t_philo *)arg);
    
    while (1)
    {
        ft_think(philo); 
        ft_eat(philo, forks);
        ft_sleep(philo);  
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

    j = 0;
    k = 0;
    num_of_philo = atoi(argv[1]);
    philos = malloc(sizeof(t_philo) * num_of_philo);
    create_philosophers_id(philos, num_of_philo);
    threads = malloc(sizeof(pthread_t) * num_of_philo);
    pthread_mutex_t *forks;
    forks = malloc(sizeof(pthread_mutex_t) * num_of_philo);

    for (int i = 0; i < num_of_philo; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }
 
    while (j < num_of_philo)
    {
        int *id = malloc(sizeof(int));
        *id = j;
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
    return(0);
}