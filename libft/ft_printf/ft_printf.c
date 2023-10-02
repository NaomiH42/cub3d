/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:49:59 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/23 11:23:04 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	check_per(char c, va_list args, char *flags)
{
	size_t	len;
	t_print	*tab;

	tab = (t_print *)malloc(sizeof(t_print));
	len = 0;
	if (c == 'c')
		len = ft_putchar(va_arg(args, int), flags, 1);
	if (c == 's')
		len = ft_putstr(va_arg(args, char *), flags, 1);
	if (c == 'p')
		len = putmem(va_arg(args, unsigned long long), flags, tab);
	if (c == 'd' || c == 'i')
		len = ft_putnbr(va_arg(args, int), flags, tab);
	if (c == 'u')
		len = ft_putnbrun(va_arg(args, unsigned int), flags, tab);
	if (c == 'x')
		len = hexalow(va_arg(args, unsigned int), flags, tab);
	if (c == 'X')
		len = hexaup(va_arg(args, unsigned int), flags, tab);
	if (c == '%')
		len = perc();
	free(tab);
	return (len);
}

static size_t	flag_mal(const char *s)
{
	int		len;
	size_t	i;

	i = 0;
	len = 0;
	while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'd'
		&& s[i] != 'i' && s[i] != 'u' && s[i] != 'x'
		&& s[i] != 'X' && s[i] != '%')
	{
		i++;
		len++;
	}
	return (len);
}

size_t	ret_free(t_ducktape *start)
{
	size_t	ret;

	ret = start->total;
	free(start);
	return (ret);
}

int	ft_printf(const char *s, ...)
{
	t_ducktape	*start;
	va_list		args;

	start = (t_ducktape *)malloc(sizeof(t_ducktape));
	start_fcn(start);
	va_start(args, s);
	while (*s)
	{
		start->l = 0;
		if (*s == '%')
		{
			start->len = flag_mal(++s);
			start->flags = (char *)malloc(sizeof(char) * (start->len + 1));
			while (start->len-- > 0)
				start->flags[start->l++] = *(s++);
			start->flags[start->l] = '\0';
			start->total += check_per(*(s++), args, start->flags);
			free(start->flags);
		}
		else
			start->total += ft_putchar(*(s++), start->flags, 0);
	}
	va_end(args);
	return (ret_free(start));
}
