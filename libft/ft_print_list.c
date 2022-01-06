/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:24:10 by jbettini          #+#    #+#             */
/*   Updated: 2022/01/04 15:27:40 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_print_list(t_list *lst)
{
    while(lst)
    {
        ft_putstr(lst->content);
        ft_putchar('\n');
        lst = lst->next;
    }
}

void    ft_print_nlist(t_list *lst, int n)
{
	int	i;

	i = 0;
    while(lst && i < n)
    {
        ft_putstr(lst->content);
        ft_putchar('\n');
        lst = lst->next;
		i++;
    }
}