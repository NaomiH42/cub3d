/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:42:25 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/21 23:42:48 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_in(char c, char *flags)
{
	size_t	i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	dot(char *flags)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	if (!flags)
		return (0);
	while (flags[i])
	{
		if (flags[i] == '.' && flags[i + 1])
		{
			i++;
			while ((flags[i] >= '0' && flags[i] <= '9'))
			{
				if (flags[i] != '.')
					res = (res * 10) + flags[i] - '0';
				i++;
			}
		}
		else
			i++;
	}
	return (res);
}

size_t	zero(char *flags)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	if (!flags)
		return (0);
	if (flags[0] == '0' && flags[i + 1])
	{
		i++;
		while ((flags[i] >= '0' && flags[i] <= '9'))
		{
			res = (res * 10) + flags[i] - '0';
			i++;
		}
	}
	return (res);
}

size_t	minus(char *flags)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	if (!flags)
		return (0);
	while (flags[i])
	{
		if (flags[i] == '-' && flags[i + 1])
		{
			i++;
			while (flags[i] >= '0' && flags[i] <= '9')
			{
				res = (res * 10) + flags[i] - '0';
				i++;
			}
		}
		if (flags[i])
			i++;
	}
	return (res);
}

size_t	space(char *flags)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	if (!flags)
		return (0);
	while (flags[i])
	{
		if ((flags[0] >= '0' && flags[0] <= '9') || flags[0] == ' ')
		{
			while ((flags[i] >= '0' && flags[i] <= '9'))
			{
				res = (res * 10) + flags[i] - '0';
				i++;
			}
			break ;
		}
		i++;
	}
	if (!is_in('.', flags) && flags[0] == '0')
		return (0);
	return (res);
}
