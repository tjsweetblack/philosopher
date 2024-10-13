/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:33:52 by badriano          #+#    #+#             */
/*   Updated: 2024/10/12 23:33:45 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*philosopher_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
