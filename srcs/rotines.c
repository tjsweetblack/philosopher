/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:20:09 by badriano          #+#    #+#             */
/*   Updated: 2024/10/12 23:38:12 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_think(t_philo philo)
{
	if (philo.env->is_running == 0)
	{
		return ;
	}
	print_philo_message("THINK", philo);
}

void	ft_right_fork(t_philo philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo.id - 1]);
	if (philo.env->is_running == 1)
	{
		print_philo_message("FORK", philo);
	}
}

void	ft_left_fork(t_philo philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo.id % philo.env->num_of_philo]);
	if (philo.env->is_running == 1)
	{
		print_philo_message("FORK", philo);
	}
}

void	ft_eat(t_philo *philo, pthread_mutex_t *forks)
{
	ft_right_fork(*philo, forks);
	ft_left_fork(*philo, forks);
	// Lock the meal lock
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time(philo->env->start_time);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->meal_lock);
	philo->eat_count++;
	if (philo->env->is_running)
	{
		printf("%ld %d is eating\n",
		get_current_time(philo->env->start_time), philo->id);
	}
	usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(&forks[philo->id - 1]);
	pthread_mutex_unlock(&forks[philo->id % philo->env->num_of_philo]);
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->meal_lock); 
	if (philo->env->is_running == 0)
	{
		return ;
	}
	if (philo->env->meals_required != -1
		&& philo->eat_count >= philo->env->meals_required)
		philo->meals_finished = 1;
}

void	ft_sleep(t_philo philo)
{
	if (philo.env->is_running == 0)
	{
		return ;
	}
	print_philo_message("SLEEP", philo);
	usleep(philo.env->time_to_sleep);
	// Sleep for 200ms
}
