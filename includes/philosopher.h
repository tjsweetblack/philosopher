/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <belmiro@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:10:39 by badriano          #+#    #+#             */
/*   Updated: 2024/10/07 08:57:21 by badriano         ###   ########.fr       */
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

/*typedef struct s_status
{
    int		dead;
    int     sleep;
    int     eat;
    int     think;
} t_status;*/

typedef struct s_env
{
    long    start_time;
    int		num_of_philo;
    int		time_to_die;
    int		time_to_eat;
    int		time_to_sleep;
    int		meals_required;
    int		is_running;
    pthread_mutex_t msg;
} t_env;
typedef struct s_philo
{
    int 		    id;
    int 		    eat_count;
    long		    last_meal_time;
    long		    time_to_die;
    long		    start_time;
    pthread_mutex_t	*fork;
    pthread_mutex_t	msg;
    pthread_mutex_t	meal_lock;
    int 		    is_eating; // Number of meals required to stop (optional)
    int 		    meals_finished;
    struct s_env	*env;   
}	t_philo;
//typedef struct s_data		t_data;
//typedef struct timeval	t_time
//typedef struct s_mutex	t_mutex;
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
void	*monitor_philosophers(void *arg);
void	initiate_threads(int argc, char **argv);
void	create_philosophers_id(t_philo *philos, int num_of_philo, pthread_mutex_t *forks, char **args, int argc);

//------------------
#endif
