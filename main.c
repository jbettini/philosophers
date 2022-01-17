/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:28:31 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/17 04:28:09 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free_exit(t_simul *simul, int mod)
{
    int i;

    i = -1;
    while (++i < simul->param.philo_nb && mod)
        pthread_join(simul->philo[i].thread, NULL);
    i = -1;
    while (++i < simul->param.philo_nb)
        pthread_mutex_destroy(&(simul->fork[i]));
    free(simul->fork);
    free(simul->philo);
}

void    take_fork(t_simul *simul, t_philo *philo)
{
    if (philo->number % 2)
    {
        pthread_mutex_lock(&(simul->fork[philo->right_fork]));
        print_log(philo, get_time(), FORK);
        pthread_mutex_lock(&(simul->fork[philo->left_fork]));
        print_log(philo, get_time(), FORK);
    }
    else
    {
        pthread_mutex_lock(&(simul->fork[philo->left_fork]));
        print_log(philo, get_time(), FORK);
        pthread_mutex_lock(&(simul->fork[philo->right_fork]));
        print_log(philo, get_time(), FORK);
    }
}

void    eat(t_simul *simul, t_philo *philo)
{
    pthread_mutex_lock(&(simul->meal));
    print_log(philo, get_time(), EAT);
    philo->eat_time++;
    philo->last_meal = get_time();
    pthread_mutex_unlock(&(simul->meal));
    spin_sleep(simul->param.time_to_eat);
    pthread_mutex_unlock(&(simul->fork[philo->left_fork]));
    pthread_mutex_unlock(&(simul->fork[philo->right_fork]));
}

void    sleep_n_think(t_simul *simul, t_philo *philo)
{
   print_log(philo, get_time(), SLEEP); 
   spin_sleep(simul->param.time_to_sleep);
   print_log(philo, get_time(), THINK);
   usleep(100);
}

void    *the_dining(void *philo_tmp)
{
    t_philo *philo;

    philo = (t_philo *)philo_tmp;
    while (!eat_and_life(philo->simul->philo, philo->simul->param.philo_nb))
    {
        take_fork(philo->simul, philo);
        eat(philo->simul, philo);
        sleep_n_think(philo->simul, philo);
    }
    return (NULL);
}

void    the_dead(t_simul *simul)
{
    int     i;
    int     meal;
    t_philo *philo;

    philo = simul->philo;
    // usleep(simul->param.time_to_die * 8);
    while (!eat_and_life(philo, simul->param.philo_nb))
    {
        i = -1;
        while (++i < simul->param.philo_nb && !eat_and_life(philo, simul->param.philo_nb))
        {
            pthread_mutex_lock(&(simul->meal));
            meal = get_time() - philo[i].last_meal;
            if (meal > simul->param.time_to_die)
                philo[i].life = 0;
            // printf("MEALLL %d, ttd %d\n", meal, simul->param.time_to_die);
            print_log(&(philo[i]), get_time(), DIE);
            pthread_mutex_lock(&(simul->meal));
        }
    }
}

int start_dining(t_simul *simul)
{
    int i;

    i = -1;
    simul->start = get_time();
    while (++i < simul->param.philo_nb)
    {
        if (pthread_create(&(simul->philo[i].thread), NULL, &the_dining, &(simul->philo[i])))
            return (1);
    }
    the_dead(simul);
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
    // system("leaks philo");
    return (0);
}