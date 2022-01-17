/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:39:46 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/17 03:35:56 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	res;
	int	i;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg -= 2;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * neg);
}

int	eat_and_life(t_philo *philo, int len)
{
	int	i;
	int	eat_nb;

	i = -1;
	eat_nb = philo[0].simul->param.eat_nb;
	while (++i < len)
	{
		if (philo[i].life == 0)
			return (1);
		else if (philo[i].eat_time >= eat_nb && eat_nb != -42)
			return (2);
	}
	return (0);
}

void    print_log(t_philo *philo, long long time_pass, int flg)
{
	long long	time;

	if (!eat_and_life(philo->simul->philo, philo->simul->param.philo_nb))
	{
		pthread_mutex_lock(&(philo->simul->log));
		time = time_pass - philo->simul->start;
		if (flg == EAT)
			printf("%lld philo %d is eating\n", time, philo->number + 1);
		else if (flg == SLEEP)
			printf("%lld philo %d is sleeping\n", time, philo->number + 1);
		else if (flg == THINK)
			printf("%lld philo %d is thinking\n", time, philo->number + 1);
		else if (flg == FORK)
			printf("%lld philo %d has taken a fork\n", time, philo->number + 1);
		pthread_mutex_unlock(&(philo->simul->log));
	}	
	else if (eat_and_life(philo->simul->philo, philo->simul->param.philo_nb) == 1)
	{
		pthread_mutex_lock(&(philo->simul->log));
		time = time_pass - philo->simul->start;
		if (flg == DIE)
			printf("%lld philo %d died\n", time, philo->number + 1);
		pthread_mutex_unlock(&(philo->simul->log));
	}
}