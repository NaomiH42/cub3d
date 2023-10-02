/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_util3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:35:52 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/22 12:35:52 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_print	*in_flags(t_print *tab, char *flags, int nbr)
{
	tab->ret = numlen(nbr);
	tab->before = space(flags) - numlen(nbr);
	tab->dots = dot(flags) - numlen(nbr);
	tab->after = minus(flags) - numlen(nbr);
	tab->zeros = zero(flags) - numlen(nbr);
	tab->n = nbr;
	tab->un = 0;
	return (tab);
}

t_print	*in_flagsun(t_print *tab, char *flags, unsigned int nbr)
{
	tab->ret = numlenun(nbr);
	tab->before = space(flags) - numlenun(nbr);
	tab->dots = dot(flags) - numlenun(nbr);
	tab->after = minus(flags) - numlenun(nbr);
	tab->zeros = zero(flags) - numlenun(nbr);
	tab->n = 0;
	tab->un = nbr;
	tab->mem = 0;
	return (tab);
}

t_print	*in_flagshex(t_print *tab, char *flags, unsigned int nbr)
{
	tab->ret = hexalen(nbr);
	tab->before = space(flags) - hexalen(nbr);
	tab->dots = dot(flags) - hexalen(nbr);
	tab->after = minus(flags) - hexalen(nbr);
	tab->zeros = zero(flags) - hexalen(nbr);
	tab->n = 0;
	tab->un = nbr;
	tab->mem = 0;
	return (tab);
}

t_print	*in_flagsmem(t_print *tab, char *flags, unsigned long long nbr)
{
	tab->ret = ptrlen(nbr);
	tab->before = space(flags) - ptrlen(nbr);
	tab->dots = dot(flags) - ptrlen(nbr);
	tab->after = minus(flags) - ptrlen(nbr);
	tab->zeros = zero(flags) - ptrlen(nbr);
	tab->n = 0;
	tab->un = 0;
	tab->mem = nbr;
	return (tab);
}
