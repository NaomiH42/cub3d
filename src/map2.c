/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/06 16:12:02 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_start_values(char symbol, int i, int l, t_prog *prog)
{
	prog->player_y = l + 0.1;
	prog->player_x = i + 0.1;
	if (symbol == 'S')
	{
		set_start_values2(prog, 0.996673, 0.081502, 0.053791);
		prog->plane_y = -0.657804;
	}
	if (symbol == 'N')
	{
		set_start_values2(prog, -1, 0, 0);
		prog->plane_y = 0.66;
	}
	if (symbol == 'W')
	{
		set_start_values2(prog, 0.108987, -0.994043, -0.656068);
		prog->plane_y = -0.071931;
	}
	if (symbol == 'E')
	{
		set_start_values2(prog, 0.019202, -0.999816, -0.659878);
		prog->plane_y = -0.012674;
	}
}

void	set_max_l(int **max_l, char **la, int l, int i)
{
	*max_l = malloc(sizeof(int) * i + 1);
	i = -1;
	while (la[++i])
	{
		l = 0;
		while (la[i][l])
			l++;
		(*max_l)[i] = l;
	}
}

void	check_map_req(char **la, t_prog *prog)
{
	t_check_info	info;

	info.check = 0;
	info.i = -1;
	while (la[++info.i])
	{
		info.l = -1;
		while (la[info.i][++info.l])
		{
			if (la[info.i][info.l] == 'N' || la[info.i][info.l] == 'S'
				|| la[info.i][info.l] == 'E' || la[info.i][info.l] == 'W')
			{
				set_start_values(la[info.i][info.l], info.i, info.l, prog);
				if (info.check == 1)
					error_msg("Multiple spawn points.");
				info.check++;
			}
		}
	}
	if (info.check == 0)
		error_msg("No spawn point.");
	info.max_i = info.i;
	set_max_l(&(info.max_l), la, info.l, info.i);
	check_corr_symbols(la, info);
	free(info.max_l);
}

char	*ft_charjoin(char *s1, char s2)
{
	size_t	i;
	char	*res;

	i = 0;
	res = (char *)ft_calloc(sizeof(char),
			(ft_strlen(s1) + 1 + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s2;
	i++;
	res[i] = '\0';
	free (s1);
	return (res);
}

char	*get_value_texture(char *line)
{
	char	*value;
	int		i;

	i = 0;
	value = ft_strdup("");
	while (line[i] != '.')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
	{
		value = ft_charjoin(value, line[i]);
		i++;
	}
	return (value);
}
