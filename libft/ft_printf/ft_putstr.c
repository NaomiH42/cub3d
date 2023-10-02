/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:51:29 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 18:00:07 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	middle(char *flags)
{
	size_t	i;
	int		dotcheck;

	dotcheck = 0;
	i = 0;
	while (flags[i])
	{
		if (flags[i] == '.')
			dotcheck = 1;
		i++;
	}
	if (dotcheck && dot(flags) == 0)
		return (1);
	else
		return (0);
}

static size_t	nul(char *flags)
{
	if (middle(flags))
		return (ft_putstr("", flags, 1));
	else if (dot(flags) > 0 && dot(flags) < 6)
		return (ft_putstr("", flags, 1));
	else
		return (ft_putstr("(null)", flags, 1));
}

static size_t	putstr_space(char *flags)
{
	int	spaces;
	int	spaces2;

	spaces = space(flags);
	spaces2 = minus(flags);
	if (spaces > 0)
	{
		put_space(spaces);
		return (spaces);
	}
	else
	{
		put_space(spaces2);
		return (spaces);
	}
}

static int	put_str(char *s, int length, int test, int after)
{
	int	ret;

	ret = 0;
	while (*s && (length > 0 || !test))
	{
		write(1, &(*s), 1);
		s++;
		length--;
	}
	if (after > 0 && test)
		ret += put_space(after);
	return (ret);
}

size_t	ft_putstr(char *s, char *flags, int test)
{
	int	ret;
	int	before;
	int	after;
	int	length;

	ret = 0;
	length = 0;
	if (!s)
		return (nul(flags));
	else if (middle(flags) && test)
		return (putstr_space(flags));
	else
	{
		if (dot(flags) < ft_strlen(s) && dot(flags) > 0)
			length = dot(flags);
		else
			length = ft_strlen(s);
		before = space(flags) - length;
		after = minus(flags) - length;
		ret = length;
		if (before > 0 && test)
			ret += put_space(before);
		ret += put_str(s, length, test, after);
	}
	return (ret);
}
