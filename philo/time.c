/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:39:46 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/20 05:40:49 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time(void)
{
    struct timeval  t;
    long long       time;

    if (gettimeofday(&t , NULL) == -1)
        return (write(2, "Get_time Error\n", 16));
    time = (t.tv_sec * 1e3) + (t.tv_usec * 1e-3);
    return (time);
}

void    spin_sleep(long long ms)
{
    long long   start;

    start = get_time();
    while (get_time() - start < ms)
        usleep(500);
}