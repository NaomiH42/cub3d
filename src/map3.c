/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/06 16:11:38 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

void	map_test(char **la, int m[], int n)
{
	int	i;
	int	l;

	i = -1;
	while (la[++i])
	{
		l = -1;
		while (la[i][++l])
		{
			if (la[i][l] != '0' && la[i][l] != 'N' && la[i][l] != 'S'
				&& la[i][l] != 'E' && la[i][l] != 'W' && la[i][l] != 'C'
				&& la[i][l] != 'D' && la[i][l] != ' ' && la[i][l] != '1')
				error_msg("Incorrect symbol found.");
			if (la[i][l] == '0' || la[i][l] == 'N' || la[i][l] == 'S'
				|| la[i][l] == 'E' || la[i][l] == 'W' || la[i][l] == 'C'
				|| la[i][l] == 'D')
			{
				if (i == 0 || l == 0 || i == n || l == m[i]
					|| l > m[i - 1] || l > m[i + 1])
					error_msg("Not enclosed by walls.");
			}
		}
	}
}

void	check_corr_symbols2(char **la, int i, int l, t_check_info info)
{
	info.max_i -= 1;
	if (la[i][l] != '1' && la[i][l] != ' ')
	{
		if (i == 0 || l == 0 || i == info.max_i || l == info.max_l[i] - 1
			|| l >= info.max_l[i - 1] - 1 || l >= info.max_l[i + 1] - 1
			|| la[i + 1][l] == ' ' || la[i - 1][l] == ' '
			|| la[i][l + 1] == ' ' || la[i][l - 1] == ' ')
			error_msg("Map not enclosed by walls or spaces in map.");
		if (la[i][l] == 'D')
		{
			if (la[i + 1][l] != '1' || la[i - 1][l] != '1')
			{
				if (la[i][l + 1] != '1' || la[i][l - 1] != '1')
					error_msg("Incorrect door placement.");
			}
		}
	}
}

void	check_corr_symbols(char **la, t_check_info info)
{
	int	i;
	int	l;

	i = -1;
	while (la[++i])
	{
		l = -1;
		while (la[i][++l])
		{
			if (la[i][l] != '0' && la[i][l] != 'N' && la[i][l] != 'S'
				&& la[i][l] != 'E' && la[i][l] != 'W' && la[i][l] != 'C'
				&& la[i][l] != 'D' && la[i][l] != ' ' && la[i][l] != '1')
			{
				error_msg("Incorrect symbols in map.");
			}
			check_corr_symbols2(la, i, l, info);
		}
	}
}

void	set_start_values2(t_prog *p, double vec_x, double vec_y, double plane_x)
{
	p->dir_vec_x = vec_x;
	p->dir_vec_y = vec_y;
	p->plane_x = plane_x;
}
