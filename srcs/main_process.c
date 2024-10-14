/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:33:52 by badriano          #+#    #+#             */
/*   Updated: 2024/10/14 14:25:48 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	case_one(t_philo philo)
{
	ft_think(philo);
	print_philo_message("FORK",philo);
	print_philo_message("SLEEP",philo);
	usleep(philo.env->time_to_die);
	print_philo_message("DIED",philo);
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
		{
			return (NULL);
        }
		ft_think(*philo);
		if (philo->env->is_running == 0)
		{
			return (NULL);
		}
		ft_eat(philo, philo->env->fork);
		if (philo->env->is_running == 0)
		{
			return (NULL);
		}
		ft_sleep(*philo);
		if (philo->env->is_running == 0)
		{
			return (NULL);
		}
    }
	return (NULL);
}
