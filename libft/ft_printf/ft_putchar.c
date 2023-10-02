/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:51:14 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/21 23:52:34 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putchar(char c, char *flags, int test)
{
	int		before;
	int		after;
	size_t	ret;

	ret = 0;
	if (test == 1)
	{
		before = space(flags) - 1;
		after = minus(flags) - 1;
		if (before > 0)
			ret = put_space(before);
	}
	write(1, &c, 1);
	ret++;
	if (test == 1)
	{
		if (after > 0)
			ret += put_space(after);
	}
	return (ret);
}
