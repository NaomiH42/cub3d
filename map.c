/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:40:29 by ehasalu           #+#    #+#             */
/*   Updated: 2023/06/03 00:57:43 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	flood(t_map *map, int y, int x)
// {
// 	if ((*map).layouttest[y][x] == '1' || (*map).layouttest[y][x] == 'F')
// 		return (0);
// 	if ((*map).layouttest[y][x] == 'D' || (*map).layouttest[y][x] == 'E')
// 	{
// 		(*map).layouttest[y][x] = '1';
// 		return (0);
// 	}
// 	else
// 		(*map).layouttest[y][x] = 'F';
// 	flood(map, y + 1, x);
// 	flood(map, y - 1, x);
// 	flood(map, y, x - 1);
// 	flood(map, y, x + 1);
// 	return (1);
// }

// int	check_path(t_map map)
// {
// 	flood(&map, map.pcoor.y, map.pcoor.x);
// 	return (1);
// }

void	error_msg(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

// void	check_map_lines(char **layout, t_map *map, int i, int l)
// {
// 	if (i == 0 || i == (*map).h - 1 || l == 0 || l == (*map).w - 1)
// 	{
// 		if (layout[i][l] != '1')
// 			error_msg(2);
// 	}
// 	else if (layout[i][l] == 'E')
// 		function_that_does_stuff(map, i, l);
// 	else if (layout[i][l] == 'P')
// 	{
// 		(*map).st++;
// 		(*map).pcoor.x = l;
// 		(*map).pcoor.y = i;
// 	}
// 	else if (layout[i][l] == 'S')
// 	{
// 		(*map).encoor.x = l;
// 		(*map).encoor.y = i;
// 	}
// 	else if (layout[i][l] == 'C')
// 		(*map).col++;
// 	else if (layout[i][l] != '0' && layout[i][l] != '1')
// 		error_msg(5);
// }

int	map_test(char **la, int m[], int n)
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

void	check_corr_symbols(char **la, int max_i, int *max_l, t_check_info info)
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

void	set_start_values(char symbol, int i, int l, t_prog *prog)
{
	prog->player_y = l;
	prog->player_x = i;
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

void	check_map_req(char **la, t_map *map, t_prog *prog)
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
	check_corr_symbols(la, info.max_i, info.max_l, info);
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

void	get_value_color_c(char *line, t_map *map)
{
	int	i;
	int	color;
	int	rgb;

	rgb = 0;
	i = 0;
	while (rgb < 3)
	{
		color = 0;
		while (!ft_isdigit(line[i]))
			i++;
		while (ft_isdigit(line[i]))
		{
			color = color * 10 + (line[i] - '0');
			i++;
		}
		if (rgb == 0)
			map->CR = color;
		else if (rgb == 1)
			map->CG = color;
		else if (rgb == 2)
			map->CB = color;
		rgb++;
	}
}

void	get_value_color_f(char *line, t_map *map)
{
	int	i;
	int	color;
	int	rgb;

	rgb = 0;
	i = 0;
	while (rgb < 3)
	{
		color = 0;
		while (!ft_isdigit(line[i]))
			i++;
		while (ft_isdigit(line[i]))
		{
			color = color * 10 + (line[i] - '0');
			i++;
		}
		if (rgb == 0)
			map->FR = color;
		else if (rgb == 1)
			map->FG = color;
		else if (rgb == 2)
			map->FB = color;
		rgb++;
	}
}

int	check_value(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO", 2))
		map->no_t = get_value_texture(line);
	else if (!ft_strncmp(line, "SO", 2))
		map->so_t = get_value_texture(line);
	else if (!ft_strncmp(line, "EA", 2))
		map->ea_t = get_value_texture(line);
	else if (!ft_strncmp(line, "WE", 2))
		map->we_t = get_value_texture(line);
	else if (!ft_strncmp(line, "F", 1))
		get_value_color_f(line, map);
	else if (!ft_strncmp(line, "C", 1))
		get_value_color_c(line, map);
	else
		return (0);
	return (1);
}

void	get_map_info2(char **line, t_map *map1, int *fd, int *checker)
{
	*checker = 0;
	*line = get_next_line(*fd);
	while (*line != NULL && *checker < 6)
	{
		*checker += check_value(*line, map1);
		free(*line);
		*line = get_next_line(*fd);
	}
}

t_map	get_map_info(char *map_file, t_prog *prog)
{
	t_map	map1;
	int		checker;
	int		fd;
	char	*layout;
	char	*line;

	fd = open(map_file, O_RDONLY);
	layout = ft_strdup_gnl("");
	get_map_info2(&line, &map1, &fd, &checker);
	while (line != NULL)
	{
		layout = ft_strjoin_gnl(layout, line);
		free(line);
		line = get_next_line(fd);
	}
	map1.layout = ft_split(layout, '\n');
	if (!map1.layout[0])
		error_msg("No map provided.");
	map1.layouttest = ft_split(layout, '\n');
	check_map_req(map1.layout, &map1, prog);
	close(fd);
	return (map1);
}
