/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:24:31 by badriano          #+#    #+#             */
/*   Updated: 2024/10/06 14:30:18 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	check_arguments_int(char **argv)
{
	int	i;
	int	j;
	int	digit;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			digit = ft_isdigit(argv[i][j]);
			if (digit == 0)
			{
				printf("%s", "Error\n not a digit");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (check_arguments_int(argv) == 1)
			printf("%s", "running\n");
		else
			return (0);
	}
	else
	{
		printf("%s", "num of args");
		return (0);
	}
	return (1);
}
