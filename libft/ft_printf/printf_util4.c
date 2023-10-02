/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_util4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:36:41 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/23 11:18:02 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

int	numlenun(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

size_t	ptrlen(uintptr_t nbr)
{
	size_t	len;

	len = 2;
	if (!nbr)
		return (5);
	while (nbr != 0)
	{
		nbr = nbr / 16;
		len++;
	}
	return (len);
}

t_ducktape	*start_fcn(t_ducktape *start)
{
	start->total = 0;
	start->flags = NULL;
	start->len = 0;
	start->l = 0;
	return (start);
}
