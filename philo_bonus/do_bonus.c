/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:58:20 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/31 17:13:29 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(t_simul *simul, t_philo *philo)
{
	sem_wait(simul->fork);
	print_log(philo, get_time(), FORK);
	sem_wait(simul->fork);
	print_log(philo, get_time(), FORK);
}

void	eat(t_simul *simul, t_philo *philo)
{
	sem_wait(simul->meal);
	philo->eat_time++;
	print_log(philo, get_time(), EAT);
	philo->last_meal = get_time();
	sem_post(simul->meal);
	spin_sleep(simul->param.time_to_eat);
	sem_post(simul->fork);
	sem_post(simul->fork);
}

void	sleep_n_think(t_simul *simul, t_philo *philo)
{
	print_log(philo, get_time(), SLEEP);
	spin_sleep(simul->param.time_to_sleep);
	print_log(philo, get_time(), THINK);
	usleep(100);
}

void	one(t_simul *simul, t_philo *philo)
{
	sem_wait(simul->fork);
	print_log(philo, get_time(), FORK);
}
