/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:28:31 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/24 05:01:37 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void    the_dining(t_philo *philo, t_simul *simul)
{
    int i = 0;
    while (simul->life == 1)
    {
        take_fork(simul, philo);
        eat(simul, philo);
        if (philo->eat_time >= philo->simul->param.eat_nb && philo->simul->param.eat_nb != -42)
            break;
        sleep_n_think(simul, philo);
    }
    exit(1);
}

void    *the_dead(void *philo_tmp)
{
    t_philo *philo;
    t_simul *simul;
    int     meal;

    philo = (t_philo *)philo_tmp;
    simul = (t_simul *)philo->simul;
    while (simul->life != 0)
    {
        sem_wait(simul->meal);
        meal = get_time() - philo->last_meal;
        if (meal > simul->param.time_to_die)
        {
            simul->life = 0;
            print_log(philo, get_time(), DIE);
            exit(1);
        }
        sem_post(simul->meal);
        if (philo->eat_time >= philo->simul->param.eat_nb && philo->simul->param.eat_nb != -42)
            break;
    }
    exit(1);
    return (NULL);
}

int start_dining(t_simul *simul)
{
    int i;

    i = -1;
    simul->start = get_time();
    while (++i < simul->param.philo_nb)
    {
        simul->philo[i].pid = fork();
        if (simul->philo[i].pid < 0)
			return (1);
        if (simul->philo[i].pid == 0)
        {
            if (pthread_create(&(simul->philo[i].death), NULL, &the_dead, &(simul->philo[i])))
                return (write(2, "Thread create Error\n", 21));
            the_dining(&(simul->philo[i]), simul);
            break ;
        }
    }
    free_exit(simul, simul->philo);
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
    return (0);
}