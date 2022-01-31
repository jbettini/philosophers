/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:00:09 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/31 17:08:12 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_param(t_param *param)
{
	if (param->philo_nb <= 0)
		return (1);
	if (param->time_to_die < 0)
		return (1);
	if (param->time_to_eat < 0)
		return (1);
	if (param->time_to_sleep < 0)
		return (1);
	return (0);
}

int	init_param(t_param *param, char **arg)
{
	param->philo_nb = ft_atoi(arg[0]);
	param->time_to_die = ft_atoi(arg[1]);
	param->time_to_eat = ft_atoi(arg[2]);
	param->time_to_sleep = ft_atoi(arg[3]);
	if (arg[4])
	{
		param->eat_nb = ft_atoi(arg[4]);
		if (param->eat_nb <= 0)
			return (1);
	}
	else
		param->eat_nb = -42;
	if (check_param(param))
		return (1);
	return (0);
}

int	init_sem(t_simul *simul)
{
	sem_unlink("/fork");
	simul->fork = sem_open("/fork", O_CREAT \
			| O_EXCL, 777, simul->param.philo_nb);
	if (simul->fork <= 0)
		return (1);
	sem_unlink("/log");
	simul->log = sem_open("/log", O_CREAT | O_EXCL, 777, 1);
	if (simul->log <= 0)
		return (1);
	sem_unlink("/meal");
	simul->meal = sem_open("/meal", O_CREAT | O_EXCL, 777, 1);
	if (simul->meal <= 0)
		return (1);
	sem_unlink("/end");
	simul->end = sem_open("/end", O_CREAT | O_EXCL, 777, 0);
	if (simul->end <= 0)
		return (1);
	sem_unlink("/feed");
	simul->feed = sem_open("/feed", O_CREAT | O_EXCL, 777, 0);
	if (simul->feed <= 0)
		return (1);
	return (0);
}

int	init_philo(t_simul *simul)
{
	int	i;

	i = -1;
	simul->philo = malloc(sizeof(t_philo) * simul->param.philo_nb);
	if (!(simul->philo))
		return (1);
	while (++i < simul->param.philo_nb)
	{
		simul->philo[i].simul = simul;
		simul->philo[i].number = i;
		simul->philo[i].left_fork = i;
		if (i + 1 < simul->param.philo_nb)
			simul->philo[i].right_fork = i + 1;
		else
			simul->philo[i].right_fork = 0;
		simul->philo[i].last_meal = get_time();
		simul->philo[i].eat_time = 0;
	}
	return (0);
}

int	project_init(t_simul *simul, char **param)
{
	if (init_param(&(simul->param), param))
		return (1);
	if (init_sem(simul))
		return (2);
	if (init_philo(simul))
		return (3);
	simul->life = 1;
	return (0);
}
