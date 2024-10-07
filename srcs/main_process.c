/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:33:52 by badriano          #+#    #+#             */
/*   Updated: 2024/10/06 15:16:02 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*philosopher_process(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->is_running)
	{
		if (philo->is_running == 0)
		{
			return (NULL);
        }
		ft_think(*philo);
		if (philo->is_running == 0)
		{
			return (NULL);
		}
		ft_eat(philo, philo->fork);
		if (philo->is_running == 0)
		{
			return (NULL);
		}
		ft_sleep(*philo);
		if (philo->is_running == 0)
		{
			return (NULL);
		}
    }
	return (NULL);
}