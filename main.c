/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:42 by badriano          #+#    #+#             */
/*   Updated: 2024/08/27 11:02:53 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosopher.h"

void check_arguments(char **argv)
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
                ft_printf("%s", "Error\n not a digit");
                exit(0);
            }
            j++;
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    if (argc == 5)
    {
        check_arguments(argv);
        ft_printf("%s", "run");
    }
    else
    {
        ft_printf("%s", "num of args");
    }
    return(0);
}