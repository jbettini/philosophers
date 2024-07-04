/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:44:06 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/28 11:45:50 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	init_mutex(t_simul *simul)
{
	int	i;

	i = 0;
	simul->fork = malloc(sizeof(pthread_mutex_t) * simul->param.philo_nb);
	if (!(simul->fork))
		return (1);
	while (i < simul->param.philo_nb)
	{
		if (pthread_mutex_init(&(simul->fork[i]), NULL))
			return (1);
		i++;
	}
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
		simul->philo[i].life = 1;
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
	if (init_mutex(simul))
		return (2);
	if (init_philo(simul))
		return (3);
	return (0);
}
