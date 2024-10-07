/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 15:20:09 by badriano          #+#    #+#             */
/*   Updated: 2024/10/07 09:21:20 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_think(t_philo philo)
{
	if (philo.is_running == 0)
	{
		return ;
	}
	printf("%ld philosopher %d is thinking\n",
		get_current_time(philo.start_time), philo.id);
}

void	ft_right_fork(t_philo philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo.id - 1]);
	if (philo.is_running)
	{
		print_philo_message("held the right fork", philo);
	}
}

void	ft_left_fork(t_philo philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo.id % philo.total_philos]);
	if (philo.is_running)
	{
		print_philo_message("held the left fork", philo);
	}
}

void	ft_eat(t_philo *philo, pthread_mutex_t *forks)
{
	ft_right_fork(*philo, forks);
	ft_left_fork(*philo, forks);
	pthread_mutex_lock(&philo->meal_lock); // Lock access to last_meal_time
	philo->last_meal_time = get_current_time(philo->start_time);
	philo->is_eating = 1;                    // Mark philosopher as eating
	pthread_mutex_unlock(&philo->meal_lock); // Unlock access
	philo->eat_count++;
	if (philo->is_running)
	{
		printf("%ld philosopher %d is eating\n",
			get_current_time(philo->start_time), philo->id);
	}
	usleep(philo->time_to_eat); // Eating for 200ms
	pthread_mutex_unlock(&forks[philo->id - 1]);
	pthread_mutex_unlock(&forks[philo->id % philo->total_philos]);
	pthread_mutex_lock(&philo->meal_lock);  
		// Lock access again before changing the state
	philo->is_eating = 0;                    // Mark philosopher as done eating
	pthread_mutex_unlock(&philo->meal_lock); // Unlock access
	if (philo->is_running == 0)
	{
		return ;
	}
	if (philo->meals_required != -1
		&& philo->eat_count >= philo->meals_required)
		philo->meals_finished = 1;
}
void	ft_sleep(t_philo philo)
{
	if (philo.is_running == 0)
	{
		return ;
	}
	printf("%ld philosopher %d is sleeping\n",
		get_current_time(philo.start_time), philo.id);
	usleep(philo.time_to_sleep); // Sleep for 200ms
}