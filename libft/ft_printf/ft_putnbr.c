/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:51:23 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 17:59:17 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prnum(int n, char *flags)
{
	char	num;

	if (n == -2147483648)
	{
		ft_putchar('-', flags, 0);
		ft_putchar('2', flags, 0);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-', flags, 0);
		n *= -1;
	}
	if (n >= 10)
	{
		prnum(n / 10, flags);
		prnum(n % 10, flags);
	}
	else
	{
		num = n + '0';
		ft_putchar(num, flags, 0);
	}
}

static size_t	zero_add(int n, char *flags, int zeros)
{
	int	ret;

	ret = 0;
	if (flags[0] == '0' && zeros > 0)
	{
		if (n < 0)
		{
			ft_putchar('-', flags, 0);
			n *= -1;
		}
		ret += put_zero(zeros);
	}
	else if (is_in('+', flags) && n >= 0)
		ret += ft_putchar('+', flags, 0);
	else if (is_in(' ', flags) && n >= 0)
		ret += ft_putchar(' ', flags, 0);
	return (ret);
}

static t_print	*something(int n, char *flags, t_print *tab)
{
	if (tab->before > 0)
	{
		if (tab->n < 0 && tab->dots > 0)
			tab->before--;
		if (tab->n < 0 && (dot(flags) - numlen(n) == 0))
			tab->before--;
		if (tab->dots > 0)
			tab->before -= tab->dots;
		tab->zeros -= tab->before;
		if (tab->before > 0)
			tab->ret += put_space(tab->before);
	}
	tab->ret += zero_add(n, flags, tab->zeros);
	if (flags[0] == '0' && tab->zeros > 0 && tab->n < 0)
		tab->n *= -1;
	if (flags[0] == '0' && tab->zeros > 0)
		tab->dots = 0;
	if (tab->dots == 0 && numlen(tab->n) != 0 && tab->n < 0)
	{
		ft_putchar('-', flags, 0);
		tab->ret += ft_putchar('0', flags, 0);
		tab->n *= -1;
	}
	return (tab);
}

static t_print	*toolong(int n, char *flags, t_print *tab)
{
	if (tab->n < 0)
	{
		ft_putchar('-', flags, 0);
		tab->n = n * -1;
		tab->ret += put_zero(tab->dots + 1);
		tab->dots++;
	}
	else
		tab->ret += put_zero(tab->dots);
	return (tab);
}

size_t	ft_putnbr(int n, char *flags, t_print *tab)
{
	in_flags(tab, flags, n);
	if (is_in('.', flags) && tab->n == 0 && tab->dots < 0)
		return (ft_putstr("", flags, 1));
	something(n, flags, tab);
	if (is_in('.', flags) && tab->dots > 0)
		toolong(n, flags, tab);
	prnum(tab->n, flags);
	if (!is_in('+', flags) && !is_in(' ', flags) && tab->after > 0)
	{
		if (tab->n < 0 && tab->dots > 0)
			tab->after--;
		if (tab->dots > 0)
			tab->after -= tab->dots;
		tab->ret += put_space(tab->after);
	}
	return (tab->ret);
}
