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
			map->cr = color;
		else if (rgb == 1)
			map->cg = color;
		else if (rgb == 2)
			map->cb = color;
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
			map->fr = color;
		else if (rgb == 1)
			map->fg = color;
		else if (rgb == 2)
			map->fb = color;
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
	if (fd == -1)
		error_msg("Map doesn't exists or whatever.");
	layout = ft_strdup_gnl("");
	get_map_info2(&line, &map1, &fd, &checker);
	while (line != NULL)
	{
		layout = ft_strjoin_gnl(layout, line);
		free(line);
		line = get_next_line(fd);
	}
	map1.layout = ft_split(layout, '\n');
	free(layout);
	if (!map1.layout[0])
		error_msg("No map provided.");
	check_map_req(map1.layout, prog);
	close(fd);
	return (map1);
}
