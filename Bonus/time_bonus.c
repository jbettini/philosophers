/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 12:14:12 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/01 00:54:09 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	t;
	long long		time;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1e3) + (t.tv_usec * 1e-3);
	return (time);
}

void	spin_sleep(long long ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(500);
}

void	ft_sem_destroy(char *name, sem_t *sem)
{
	sem_unlink(name);
	sem_close(sem);
}
