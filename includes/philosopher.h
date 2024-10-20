/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:39 by badriano          #+#    #+#             */
/*   Updated: 2024/10/19 23:50:57 by badriano         ###   ########.fr       */
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
#include <string.h>

typedef struct s_env
{
    long    start_time;
    int		num_of_philo;
    int		time_to_die;
    int		time_to_eat;
    int		time_to_sleep;
    pthread_mutex_t	meal_lock;
    int		meals_required;
    int     cycle_count;
    int     total_times_eaten;
    int     philos_finished_in_cycle;
    int		is_running;
    pthread_mutex_t	*fork;
    pthread_mutex_t msg;
} t_env;

typedef struct s_philo
{
    int 		    id;
    int 		    eat_count;
    long		    last_meal_time;
    int 		    is_eating;
    int 		    cycle_flag;
    int 		    meals_finished;
    struct s_env	*env; 
}	t_philo;
//------------------printf-------------------------
int		ft_putchar_len(char c, int current_len);
int		ft_print_num(int num, int current_len);
int		num_len(int num, int current_len);
int		ft_putstr(char *str, int current_len);
int		ft_printf(const char *str, ...);
long    ft_atol(const char *str);
long    get_time(void);
long    get_current_time(long start);
int     ft_isdigit(int c);
int     check_arguments(int argc, char **argv);
int     check_arguments_int(char **argv);
void	*philosopher_process(void *arg);
void	ft_sleep(t_philo philo);
void	ft_eat(t_philo *philo, pthread_mutex_t *forks);
void	ft_think(t_philo philo);
void	print_philo_message(char *message, t_philo philo);
int     ft_strcmp(char *s1, char *s2);
void	initiate_threads(int argc, char **argv);
void	*ft_monitoring(void *args);
void	store_to_struct(t_philo *philos, int num_of_philo, pthread_mutex_t *forks, char **args, int argc);

//------------------
#endif
