/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:46:50 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/31 17:21:15 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*the_dining(void *philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	if (philo->simul->param.philo_nb == 1)
		one(philo->simul, philo);
	else
	{
		while (!eat_and_life(philo->simul->philo, philo->simul->param.philo_nb))
		{
			take_fork(philo->simul, philo);
			eat(philo->simul, philo);
			sleep_n_think(philo->simul, philo);
		}
	}
	return (NULL);
}

void	the_dead(t_simul *simul)
{
	int		i;
	int		meal;
	t_philo	*philo;

	philo = simul->philo;
	while (!eat_and_life(philo, simul->param.philo_nb))
	{
		i = -1;
		while (++i < simul->param.philo_nb && \
				!eat_and_life(philo, simul->param.philo_nb))
		{
			pthread_mutex_lock(&(simul->meal));
			meal = get_time() - philo[i].last_meal;
			if (meal >= simul->param.time_to_die)
			{
				philo[i].life = 0;
				print_log(&(philo[i]), get_time(), DIE);
			}
			pthread_mutex_lock(&(simul->meal));
		}
	}
}

int	start_dining(t_simul *simul)
{
	int	i;

	i = -1;
	simul->start = get_time();
	while (++i < simul->param.philo_nb)
	{
		if (pthread_create(&(simul->philo[i].thread), NULL, \
					&the_dining, &(simul->philo[i])))
			return (1);
	}
	the_dead(simul);
	return (0);
}

int	main(int ac, char **av)
{
	t_simul	simul;
	int		ret;

	if (ac != 5 && ac != 6)
		return (write(2, "Invalid number of argument\n", 27));
	else
	{
		ret = project_init(&simul, &av[1]);
		if (ret)
		{
			if (ret == 3)
				free(simul.fork);
			return (write(2, "Initialising error\n", 19));
		}
		if (start_dining(&simul))
		{
			free_exit(&simul, 0);
			return (write(2, "Thread create error\n", 21));
		}
		else
			free_exit(&simul, 1);
	}
	return (0);
}
