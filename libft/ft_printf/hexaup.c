/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexaup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:16:02 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 18:00:33 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hexaupprint(unsigned int nbr, char *flags)
{
	if (nbr >= 16)
	{
		hexaupprint(nbr / 16, flags);
		hexaupprint(nbr % 16, flags);
	}
	else if (nbr <= 9)
		ft_putchar((nbr + '0'), flags, 0);
	else if (nbr < 16)
		ft_putchar(nbr - 10 + 'A', flags, 0);
}

static t_print	*lineshex(char *flags, t_print *tab)
{	
	if (flags[0] == '0' && tab->zeros > 0)
	{
		tab->dots = 0;
		tab->ret += put_zero(tab->zeros);
	}
	else if (is_in('+', flags))
		tab->ret += ft_putchar('+', flags, 0);
	else if (is_in(' ', flags))
		tab->ret += ft_putchar(' ', flags, 0);
	return (tab);
}

size_t	hexaup(unsigned int n, char *flags, t_print *tab)
{
	in_flagshex(tab, flags, n);
	tab->ret += sharpup(flags, n);
	if (is_in('.', flags) && tab->un == 0 && tab->dots < 0)
	{
		tab->ret = ft_putstr("", flags, 1);
		return (tab->ret);
	}	
	if (tab->before > 0)
	{
		if (tab->dots > 0)
			tab->before -= tab->dots;
		tab->zeros -= tab->before;
		if (tab->before > 0)
			tab->ret += put_space(tab->before);
	}
	lineshex(flags, tab);
	if (is_in('.', flags) && tab->dots > 0)
		tab->ret += put_zero(tab->dots);
	hexaupprint(tab->un, flags);
	if (!is_in('+', flags) && !is_in(' ', flags) && tab->after > 0)
		if (tab->dots > 0)
			tab->after -= tab->dots;
	if (!is_in('+', flags) && !is_in(' ', flags) && tab->after > 0)
		tab->ret += put_space(tab->after);
	return (tab->ret);
}
