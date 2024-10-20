/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:33:52 by badriano          #+#    #+#             */
/*   Updated: 2024/10/19 23:59:38 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	case_one(t_philo philo)
{
	ft_think(philo);
	print_philo_message("FORK",philo);
	print_philo_message("SLEEP",philo);
	usleep(10); 
	print_philo_message("DIED",philo);	
}
void	ft_reset_cycle(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->env->num_of_philo)
	{
		philo[i].cycle_flag = 0;
		i++;
	}
	philo->env->cycle_count = 0;
}
void	*philosopher_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if(philo->env->num_of_philo == 1)
	{
		case_one(philo[0]);
		return (NULL);
	}
	while (philo->env->is_running)
	{
		if (philo->env->is_running == 0)
			return (NULL);
		ft_think(*philo);
		if (philo->env->is_running == 0)
			return (NULL);
		if(philo->cycle_flag != 1 && philo->eat_count != philo->env->meals_required)
			ft_eat(philo, philo->env->fork);
		if (philo->env->is_running == 0)
			return (NULL);
		ft_sleep(*philo);
		if (philo->env->is_running == 0)
			return (NULL);
		if(philo->env->cycle_count == philo->env->num_of_philo)
			ft_reset_cycle(philo);
    }
	return (NULL);
}
