/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 10:28:29 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 12:28:20 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	put_space(size_t n)
{
	size_t	i;
	char	space;

	space = ' ';
	i = 0;
	while (i < n)
	{
		write(1, &space, 1);
		i++;
	}
	return (i);
}

size_t	put_zero(size_t n)
{
	size_t	i;
	char	zero;

	zero = '0';
	i = 0;
	while (i < n)
	{
		write(1, &zero, 1);
		i++;
	}
	return (i);
}

size_t	sharplow(char *flags, unsigned int n)
{
	if (is_in('#', flags) && n != 0)
	{
		ft_putchar('0', flags, 0);
		ft_putchar('x', flags, 0);
		return (2);
	}
	return (0);
}

size_t	sharpup(char *flags, unsigned int n)
{
	if (is_in('#', flags) && n != 0)
	{
		ft_putchar('0', flags, 0);
		ft_putchar('X', flags, 0);
		return (2);
	}
	return (0);
}

size_t	hexalen(unsigned int nbr)
{
	size_t	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / 16;
		len++;
	}
	return (len);
}
