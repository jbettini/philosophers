/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 09:11:15 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/06 11:28:17 by jbettini         ###   ########.fr       */
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

typedef struct s_philo
{
    int number;
	int life;
    int state;
	struct s_philo	*next;
}				t_philo;

typedef struct s_param
{
    int philo_nb;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_nb;
}				t_param;



#endif