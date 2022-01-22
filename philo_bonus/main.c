/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:28:31 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/22 08:49:32 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    the_dining(void *tmp_philo)
{
    t_philo *philo;

    philo = (t_philo *)tmp_philo;
    if (philo->simul->param.philo_nb == 1)
        one(philo->simul, philo);
    else
    {
        while (philo->simul->life == 1)
        {
            take_fork(philo->simul, philo);
            eat(philo->simul, philo);
            if (philo->eat_time >= philo->simul->param.eat_nb && philo->simul->param.eat_nb != -42)
                break ;
            sleep_n_think(philo->simul, philo);
        }
    }
}

void    *the_dead(void *philo_tmp)
{
    int     meal;
    t_philo *philo;
    int     i;

    i = -1;
    philo = (t_philo *)philo_tmp;
    while (philo->simul->life)
    {
        sem_wait(philo->simul->meal);
        meal = get_time() - philo->last_meal;
        if (meal > philo->simul->param.time_to_die)
        {
            philo->simul->life = 0;
            print_log(philo, get_time(), DIE);
            sem_wait(philo->simul->log);
            free_exit(philo->simul);
        }
        sem_post(philo->simul->meal);
        if (philo->eat_time >= philo->simul->param.eat_nb && philo->simul->param.eat_nb != -42)
            break ;
    }
    return (NULL);
}

int start_dining(t_simul *simul)
{
	int i;

	i = -1;
	simul->start = get_time();
	while (++i < simul->param.philo_nb)
	{
		usleep(100);
		simul->philo[i].pid = fork();
		if (simul->philo[i].pid < 0)
			return (1);
		if (simul->philo[i].pid == 0)
        {
			if (pthread_create(&(simul->philo[i].death), NULL, &the_dead, &(simul->philo[i])))
                return (write(2, "Thread creat Error\n", 1));
            the_dining(&(simul->philo[i]));
        }
	}
    free_exit(simul);
	return (0);
}

int main(int ac, char **av)
{
    t_simul simul;
    int     ret;

    if (ac != 5 && ac != 6)
        return(write(2, "Invalid number of argument\n", 27));
    else 
    {
        ret = project_init(&simul, &av[1]);
        if (ret)
           return(write(2, "Initialising error\n", 20));
        else
            start_dining(&simul);    
    }
    // system("leaks philo");
    return (0);
}