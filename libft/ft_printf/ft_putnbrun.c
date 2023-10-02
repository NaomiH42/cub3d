/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:56:35 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 18:00:49 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prnumun(unsigned int n, char *flags)
{
	char	num;

	if (n >= 10)
	{
		prnumun(n / 10, flags);
		prnumun(n % 10, flags);
	}
	else
	{
		num = n + '0';
		ft_putchar(num, flags, 0);
	}
}

static t_print	*manylines(char *flags, t_print *tab)
{
	if (tab->before > 0)
	{
		if (tab->dots > 0)
			tab->before -= tab->dots;
		tab->zeros -= tab->before;
		if (tab->before > 0)
			tab->ret += put_space(tab->before);
	}
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

size_t	ft_putnbrun(unsigned int n, char *flags, t_print *tab)
{
	in_flagsun(tab, flags, n);
	if (is_in('.', flags) && tab->un == 0 && tab->dots < 0)
	{
		tab->ret = ft_putstr("", flags, 1);
		return (tab->ret);
	}
	manylines(flags, tab);
	if (is_in('.', flags) && tab->dots > 0)
		tab->ret += put_zero(tab->dots);
	prnumun(tab->un, flags);
	if (!is_in('+', flags) && !is_in(' ', flags) && tab->after > 0)
	{
		if (tab->dots > 0)
			tab->after -= tab->dots;
		tab->ret += put_space(tab->after);
	}
	return (tab->ret);
}
