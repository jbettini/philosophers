/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:39:46 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/24 04:58:19 by jbettini         ###   ########.fr       */
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

void    print_log(t_philo *philo, long long time_pass, int flg)
{
	long long	time;

	if (philo->simul->life == 1 && flg != DIE)
	{
		sem_wait(philo->simul->log);
		time = time_pass - philo->simul->start;
		if (flg == EAT)
			printf("%lld philo %d is eating\n", time, philo->number + 1);
		else if (flg == SLEEP)
			printf("%lld philo %d is sleeping\n", time, philo->number + 1);
		else if (flg == THINK)
			printf("%lld philo %d is thinking\n", time, philo->number + 1);
		else if (flg == FORK)
			printf("%lld philo %d has taken a fork\n", time, philo->number + 1);
		if (philo->eat_time >= philo->simul->param.eat_nb && philo->simul->param.eat_nb != -42)
			sem_post(philo->simul->end);
		else
			sem_post(philo->simul->log);
	}	
	else if (philo->simul->life == 0 && flg == DIE)
	{
		sem_wait(philo->simul->log);
		time = time_pass - philo->simul->start;
		if (flg == DIE)
			printf("%lld philo %d died\n", time, philo->number + 1);
		sem_post(philo->simul->end);
	}
}

void	ft_destroy_sem(char *name, sem_t *sem)
{
	sem_unlink(name);
	sem_close(sem);
}

int	parent(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->simul->param.philo_nb)
	{
		if (philo[i].pid == 0)
			return (0);
		i++;
	}
	return (1);
}

void    free_exit(t_simul *simul, t_philo *philo)
{
	int	i;

	i = -1;
	sem_wait(philo->simul->end);
	if (parent(philo))
	{
		while (++i < simul->param.philo_nb)
			kill(philo[i].pid, 15);
		i = -1;
		while (++i < simul->param.philo_nb)
			waitpid(philo[i].pid, NULL, 0);
	}
	free(simul->philo);
}
