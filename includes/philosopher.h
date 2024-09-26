/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:39 by badriano          #+#    #+#             */
/*   Updated: 2024/09/26 18:42:57 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/*typedef struct s_status
{
    int		dead;
    int     sleep;
    int     eat;
    int     think;
} t_status;*/


typedef struct s_philo
{
    int 		 id;
    int 		 eat_count;
    pthread_mutex_t	*fork;
    int 		 total_philos;
}	t_philo;
//typedef struct s_data		t_data;
//typedef struct timeval	t_time;
//typedef struct s_mutex	t_mutex;
//------------------printf-------------------------
int		ft_putchar_len(char c, int current_len);
int		ft_print_num(int num, int current_len);
int		num_len(int num, int current_len);
int		ft_putstr(char *str, int current_len);
int		ft_printf(const char *str, ...);
int		ft_atoi(const char *str);
int     ft_isdigit(int c);
//------------------
#endif
