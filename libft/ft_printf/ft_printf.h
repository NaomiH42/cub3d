/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:49 by ehasalu           #+#    #+#             */
/*   Updated: 2023/01/23 11:18:36 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>

typedef struct s_ducktape
{
	size_t	total;
	char	*flags;
	int		len;
	size_t	l;
}	t_ducktape;

typedef struct s_print
{
	unsigned long long	mem;
	unsigned int		un;
	int					ret;
	int					before;
	int					dots;
	int					after;
	int					zeros;
	int					n;
}	t_print;

t_ducktape	*start_fcn(t_ducktape *start);
t_print		*in_flagsmem(t_print *tab, char *flags, unsigned long long nbr);
t_print		*in_flagshex(t_print *tab, char *flags, unsigned int nbr);
t_print		*in_flagsun(t_print *tab, char *flags, unsigned int nbr);
t_print		*in_flags(t_print *tab, char *flags, int nbr);
size_t		ptrlen(uintptr_t nbr);
size_t		hexalen(unsigned int nbr);
size_t		sharpup(char *flags, unsigned int n);
size_t		sharplow(char *flags, unsigned int n);
size_t		zero(char *flags);
size_t		put_zero(size_t n);
size_t		put_space(size_t n);
size_t		ft_putchar(char c, char *flags, int test);
size_t		ft_putstr(char *s, char *flags, int test);
size_t		ft_putnbr(int n, char *flags, t_print *tab);
size_t		ft_putnbrun(unsigned int n, char *flags, t_print *tab);
size_t		hexalow(unsigned int nbr, char *flags, t_print *tab);
size_t		hexaup(unsigned int nbr, char *flags, t_print *tab);
size_t		putmem(unsigned long long ptr, char *flags, t_print *tab);
size_t		ft_strlen(const char *s);
size_t		perc(void);
size_t		dot(char *flags);
size_t		minus(char *flags);
size_t		space(char *flags);
int			ft_printf(const char *s, ...);
int			is_in(char c, char *flags);
int			numlenun(unsigned int n);
int			numlen(int n);

#endif
