/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:20:09 by badriano          #+#    #+#             */
/*   Updated: 2024/10/19 23:55:28 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_think(t_philo philo)
{
	if (philo.env->is_running == 0)
		return ;
	if(philo.env->num_of_philo == 1)
		print_philo_message("THINK", philo);
}

void	ft_right_fork(t_philo philo, pthread_mutex_t *forks)
{
	if (philo.env->is_running == 0)
		return ;
	pthread_mutex_lock(&forks[philo.id - 1]);
	if (philo.env->is_running == 1)
		print_philo_message("FORK", philo);
}

void	ft_left_fork(t_philo philo, pthread_mutex_t *forks)
{
	if (philo.env->is_running == 0)
		return ;
	pthread_mutex_lock(&forks[philo.id % philo.env->num_of_philo]);
	if (philo.env->is_running == 1)
		print_philo_message("FORK", philo);
}
void ft_grab_forks(t_philo *philo, pthread_mutex_t *forks)
{
    int first_fork = philo->id - 1;
    int second_fork = philo->id % philo->env->num_of_philo;
    if (first_fork > second_fork) // Always pick the smaller index fork first
    {
		ft_left_fork(*philo, forks);
		ft_right_fork(*philo, forks);
	}
    else
    {
		ft_right_fork(*philo, forks);
		ft_left_fork(*philo, forks);
    }
}

void	ft_eat(t_philo *philo, pthread_mutex_t *forks)
{
	ft_grab_forks(philo, forks);
	if (philo->env->is_running == 0)
		return ;
	philo->last_meal_time = get_current_time(philo->env->start_time);
	pthread_mutex_lock(&philo->env->meal_lock);
    philo->is_eating = 1;
	philo->cycle_flag = 1;
    philo->eat_count++;
	philo->env->cycle_count++;
	philo->env->total_times_eaten++;
	pthread_mutex_unlock(&philo->env->meal_lock);
    if (philo->env->is_running)
		print_philo_message("EAT", *philo);
	usleep(philo->env->time_to_eat);
    pthread_mutex_unlock(&forks[philo->id - 1]);
    pthread_mutex_unlock(&forks[philo->id % philo->env->num_of_philo]);
	pthread_mutex_lock(&philo->env->meal_lock);
    philo->is_eating = 0;
	pthread_mutex_unlock(&philo->env->meal_lock);
    if (philo->env->is_running == 0)
        return ;
    if (philo->env->meals_required != -1 && philo->eat_count >= philo->env->meals_required)
        philo->meals_finished = 1;
    philo->env->philos_finished_in_cycle++;
    if (philo->env->philos_finished_in_cycle == philo->env->num_of_philo)
        philo->env->philos_finished_in_cycle = 0;  // Reset for next cycle
}


void	ft_sleep(t_philo philo)
{
	if (philo.env->is_running == 0)
		return ;
	print_philo_message("SLEEP", philo);
	usleep(philo.env->time_to_sleep);
}
