/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putmem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:01:56 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 12:30:13 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	memprint(uintptr_t nbr, char *flags)
{
	if (nbr >= 16)
	{
		memprint(nbr / 16, flags);
		memprint(nbr % 16, flags);
	}
	else if (nbr <= 9)
		ft_putchar((nbr + '0'), flags, 0);
	else if (nbr < 16)
		ft_putchar(nbr - 10 + 'a', flags, 0);
}

static void	show_adr(uintptr_t adr, char *flags)
{	
	if (!adr)
		ft_putstr("(nil)", flags, 0);
	else
	{
		ft_putchar('0', flags, 0);
		ft_putchar('x', flags, 0);
		memprint(adr, flags);
	}
}

static	t_print	*linesmem(char *flags, t_print *tab)
{
	if (flags[0] == '0' && tab->zeros > 0)
	{
		tab->dots = 0;
		tab->ret += put_zero(tab->zeros);
	}
	else if (is_in('+', flags))
		tab->ret += ft_putchar('+', flags, 0);
	else if (is_in(' ', flags) && tab->un == 0)
		tab->ret += ft_putchar(' ', flags, 0);
	if (is_in('.', flags) && tab->dots > 0)
		tab->ret += put_zero(tab->dots);
	return (tab);
}

size_t	putmem(unsigned long long n, char *flags, t_print *tab)
{
	in_flagsmem(tab, flags, n);
	if (is_in('.', flags) && tab->mem == 0 && tab->dots < 0)
	{
		tab->ret = ft_putstr("", flags, 1);
		return (tab->ret);
	}	
	if (tab->before > 0)
	{
		if (tab->dots > 0)
			tab->before -= tab->dots;
		tab->zeros -= tab->before;
		tab->ret += put_space(tab->before);
	}
	linesmem(flags, tab);
	show_adr(tab->mem, flags);
	if (!is_in('+', flags) && !is_in(' ', flags) && tab->after > 0)
	{
		if (tab->dots > 0)
			tab->after -= tab->dots;
		tab->ret += put_space(tab->after);
	}
	return (tab->ret);
}
