/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 04:45:36 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/22 08:47:51 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_fork(t_simul *simul, t_philo *philo)
{
    sem_wait(simul->fork);
    print_log(philo, get_time(), FORK);
    sem_wait(simul->fork);
    print_log(philo, get_time(), FORK);
}

void    eat(t_simul *simul, t_philo *philo)
{
    sem_wait(simul->meal);
    print_log(philo, get_time(), EAT);
    philo->eat_time++;
    if (philo->eat_time >= philo->simul->param.eat_nb && philo->simul->param.eat_nb != -42)
    {
        sem_wait(simul->log);
        free_exit(simul);
    }
    philo->last_meal = get_time();
    sem_post(simul->meal);
    spin_sleep(simul->param.time_to_eat);
    sem_post(simul->fork);
    sem_post(simul->fork);
}

void    sleep_n_think(t_simul *simul, t_philo *philo)
{
   print_log(philo, get_time(), SLEEP); 
   spin_sleep(simul->param.time_to_sleep);
   print_log(philo, get_time(), THINK);
   usleep(100);
}

void    one(t_simul *simul, t_philo *philo)
{
    sem_wait(simul->fork);
    print_log(philo, get_time(), FORK);
}