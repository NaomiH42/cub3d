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

int	flood(t_map *map, int y, int x)
{
	if ((*map).layouttest[y][x] == '1' || (*map).layouttest[y][x] == 'F')
		return (0);
	// if ((*map).layouttest[y][x] == 'C')
	// 	(*map).coltest -= 1;
	// if ((*map).layouttest[y][x] == 'E')
	// 	(*map).extest -= 1;
	if ((*map).layouttest[y][x] == 'D' || (*map).layouttest[y][x] == 'E')
	{
		(*map).layouttest[y][x] = '1';
		return (0);
	}
	else
		(*map).layouttest[y][x] = 'F';
	flood(map, y + 1, x);
	flood(map, y - 1, x);
	flood(map, y, x - 1);
	flood(map, y, x + 1);
	return (1);
}

int	check_path(t_map map)
{
	flood(&map, map.pcoor.y, map.pcoor.x);
	return (1);
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

int	map_test(char **layout, int max_l[], int max_i)
{
	int i = 0;
	int l;
	while (layout[i])
	{
		l = 0;
		while (layout[i][l])
		{
			if (layout[i][l] != '0' && layout[i][l] != 'N' && layout[i][l] != 'S'
				&& layout[i][l] != 'E' && layout[i][l] != 'W' && layout[i][l] != 'C'
				&& layout[i][l] != 'D' && layout[i][l] != ' ' && layout[i][l] != '1')
			{
				exit (0);
			}
			if (layout[i][l] == '0' || layout[i][l] == 'N' || layout[i][l] == 'S'
				|| layout[i][l] == 'E' || layout[i][l] == 'W' || layout[i][l] == 'C'
				|| layout[i][l] == 'D')
			{
				if (i == 0 || l == 0 || i == max_i || l == max_l[i] || l > max_l[i-1] || l > max_l[i+1])
				{
					printf("%d %d %d %d %d\n\n", i, l, max_l[i], max_l[i + 1], max_l[i-1]);	
					exit(0);
				}
			}
			l++;
		}
		i++;
	}
}

void	check_map_req(char **layout, t_map *map, t_prog *prog)
{
	int	i;
	int	l;
	int	check;

	check = 0;
	i = 0;
	while (layout[i])
	{
		l = 0;
		while (layout[i][l])
		{
			printf("%c", layout[i][l]);
			if (layout[i][l] == 'N' || layout[i][l] == 'S' || layout[i][l] == 'E' || layout[i][l] == 'W')
			{
				prog->player_y = l;
				prog->player_x = i;
				if (layout[i][l] == 'S')
				{
					prog->dir_vec_x = 0.996673; //s
					prog->dir_vec_y = 0.081502;
					prog->plane_x = 0.053791;
					prog->plane_y = -0.657804;
				}
				if (layout[i][l] == 'N')
				{
					prog->dir_vec_x = -1; //n
					prog->dir_vec_y = 0;
					prog->plane_x = 0;
					prog->plane_y = 0.66;
				}
				if (layout[i][l] == 'W')
				{
					prog->dir_vec_x = 0.108987; //w
					prog->dir_vec_y = -0.994043;
					prog->plane_x = -0.656068;
					prog->plane_y = -0.071931;
				}
				if (layout[i][l] == 'E')
				{
					prog->dir_vec_x = 0.019202; //e
					prog->dir_vec_y = -0.999816;
					prog->plane_x = -0.659878;
					prog->plane_y = -0.012674;
				}
				if (check == 1)
					exit (0);
				check++;
			}
			l++;
		}
		printf("\n");
		i++;
	}
	if (check == 0)
		exit (0);
		printf("%f\n%f\n%f\n%f\n", prog->player_x, prog->player_y, prog->dir_vec_x, prog->dir_vec_y);
	int	max_i = i;
	int	max_l[i+1];
	i = 0;
	while (layout[i])
	{
		l = 0;
		while (layout[i][l])
		{
			l++;
		}
		max_l[i] = l;
		printf("%d\n", max_l[i]);
		i++;
	}
	// map_test(layout, max_l, max_i);
	i = 0;
	while (layout[i])
	{
		l = 0;
		while (layout[i][l])
		{
			if (layout[i][l] != '0' && layout[i][l] != 'N' && layout[i][l] != 'S'
				&& layout[i][l] != 'E' && layout[i][l] != 'W' && layout[i][l] != 'C'
				&& layout[i][l] != 'D' && layout[i][l] != ' ' && layout[i][l] != '1')
			{
				exit (0);
			}
			if (layout[i][l] != '1' && layout[i][l] != ' ')// || layout[i][l] == 'S'
			// 	|| layout[i][l] == 'E' || layout[i][l] == 'W' || layout[i][l] == 'C'
			// 	|| layout[i][l] == 'D')
			{
				if (i == 0 || l == 0 || i == max_i || l == max_l[i] - 1 || l >= max_l[i-1] - 1 || l >= max_l[i+1] - 1
					|| layout[i + 1][l] == ' ' || layout[i - 1][l] == ' ' || layout[i][l + 1] == ' ' || layout[i][l - 1] == ' ')
				{
					printf("%d %d %d %d %d\n\n", i, l, max_l[i], max_l[i + 1], max_l[i-1]);	
					exit(0);
				}
			}
			l++;
		}
		i++;
	}

	// if (!flood(map, prog->player_x, prog->player_y))
	// 	exit (0);
	// while (layout[i])
	// {
	// 	l = 0;
	// 	if (ft_strlen(layout[0]) != ft_strlen(layout[i]))
	// 		error_msg(1);
	// 	while (layout[i][l])
	// 	{
	// 		check_map_lines(layout, map, i, l);
	// 		l++;
	// 	}
	// 	i++;
	// }
	// if ((*map).ex != 1 || (*map).st != 1 || (*map).col < 1)
	// 	error_msg(3);
	// if (!check_path(*map))
	// 	error_msg(4);
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

t_map	get_map_info(char *map_file, t_prog *prog)
{
	t_map	map1;
	int		checker;
	int		fd;
	char	*layout;
	char	*line;

	checker = 0;
	fd = open(map_file, O_RDONLY);
	layout = ft_strdup_gnl("");
	line = get_next_line(fd);
	
	while (line != NULL && checker < 6)
	{
		checker += check_value(line, &map1);
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL)
	{
		layout = ft_strjoin_gnl(layout, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!layout)
		exit(0);
	map1.layout = ft_split(layout, '\n');
	if (!map1.layout[0])
		exit(0);
	map1.layouttest = ft_split(layout, '\n');
	check_map_req(map1.layout, &map1, prog);
	// free_chars(&layout, &line);
	close(fd);
	return (map1);
}
