/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 10:15:23 by badriano          #+#    #+#             */
/*   Updated: 2024/10/14 06:53:54 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str) == 1)
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_current_time(long start)
{
	return (get_time() - start);
}

void	print_philo_message(char *message, t_philo philo)
{
	pthread_mutex_lock(&philo.env->msg);
	if (philo.env->is_running == 0)
	{
		pthread_mutex_unlock(&philo.env->msg);
		return ;
	}
	if (ft_strcmp(message, "FORK") == 0)
	{
		printf("%ld %d has taken a fork\n",
			get_current_time(philo.env->start_time), philo.id);
	}
	else if (ft_strcmp(message, "EAT") == 0)
	{
		printf("%ld %d is eating\n", get_current_time(philo.env->start_time),
			philo.id);
	}
	else if (ft_strcmp(message, "SLEEP") == 0)
	{
		printf("%ld %d is sleeping\n", get_current_time(philo.env->start_time),
			philo.id);
	}
	else if (ft_strcmp(message, "THINK") == 0)
	{
		printf("%ld %d is thinking\n", get_current_time(philo.env->start_time),
			philo.id);
	}
	else if (ft_strcmp(message, "DIED") == 0)
	{
		printf("%ld %d died\n", get_current_time(philo.env->start_time), philo.id);
		usleep(10);
	}
	pthread_mutex_unlock(&philo.env->msg);
}
