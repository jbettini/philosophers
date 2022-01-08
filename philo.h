/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 09:11:15 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/08 19:40:57 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_param
{
    int philo_nb;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_nb;
}				t_param;

typedef struct s_philo
{
    int         number;
	int         life;
    int         left_fork;
    int         right_fork;
    int         last_meal;
    int         eat_time;
    t_param     param;
    pthread_t   thread;
}				t_philo;

typedef struct s_simul
{
    t_param         param;
    t_philo         *philo;
    pthread_mutex_t *fork;
}				t_simul;

int check_param(t_param *param);
int init_param(t_param *param, char **arg);
int init_mutex(t_simul *simul);
int init_philo(t_simul *simul);
int project_init(t_simul *simul, char **param);

int ft_atoi(const char *str);

#endif