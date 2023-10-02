/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls3_n_stuff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 23:36:23 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(int degrees)
{
	return ((double)(degrees * M_PI / 180));
}

int	rgb_to_argb(int r, int g, int b)
{
	int	color;

	color = (r << 24) | (g << 16) | (b << 8) | (255);
	return (color);
}

void	move_forwards(t_prog *prog)
{
	if (prog->map.layout[(int)(prog->player_x
			+ prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == '0'
		|| prog->map.layout[(int)(prog->player_x
			+ prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 'O')
		prog->player_x += prog->dir_vec_x * prog->move_speed / 10;
	if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ prog->dir_vec_y * prog->move_speed)] == '0'
		|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ prog->dir_vec_y * prog->move_speed)] == 'O')
		prog->player_y += prog->dir_vec_y * prog->move_speed / 10;
}

void	move_backwards(t_prog *prog)
{
	if (prog->map.layout[(int)(prog->player_x - prog->dir_vec_x
			* prog->move_speed)][(int)prog->player_y] == '0'
		|| prog->map.layout[(int)(prog->player_x - prog->dir_vec_x
		* prog->move_speed)][(int)prog->player_y] == 'O')
		prog->player_x -= prog->dir_vec_x * prog->move_speed / 10;
	if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		- prog->dir_vec_y * prog->move_speed)] == '0'
		|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y
			- prog->dir_vec_y * prog->move_speed)] == 'O')
		prog->player_y -= prog->dir_vec_y * prog->move_speed / 10;
}
