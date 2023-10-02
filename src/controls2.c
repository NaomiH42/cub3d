/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 21:47:37 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left(t_prog *prog)
{
	double	x;
	double	y;

	x = -prog->dir_vec_y;
	y = prog->dir_vec_x;
	if (prog->map.layout[(int)(prog->player_x
			+ x * prog->move_speed)][(int)prog->player_y] == '0'
			|| prog->map.layout[(int)(prog->player_x + x
		* prog->move_speed)][(int)prog->player_y] == 'O')
		prog->player_x += x * prog->move_speed / 10;
	if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ y * prog->move_speed)] == '0'
		|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ y * prog->move_speed)] == 'O')
		prog->player_y += y * prog->move_speed / 10;
}

void	move_right(t_prog *prog)
{
	double	x;
	double	y;

	x = prog->dir_vec_y;
	y = -prog->dir_vec_x;
	if (prog->map.layout[(int)(prog->player_x + x
			* prog->move_speed)][(int)prog->player_y] == '0'
		|| prog->map.layout[(int)(prog->player_x + x
		* prog->move_speed)][(int)prog->player_y] == 'O')
		prog->player_x += x * prog->move_speed / 10;
	if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ y * prog->move_speed)] == '0'
		|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y
			+ y * prog->move_speed)] == 'O')
		prog->player_y += y * prog->move_speed / 10;
}

void	rotate_right(t_prog *prog)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = prog->dir_vec_x;
	prog->dir_vec_x = prog->dir_vec_x * cos(-prog->rotate_speed)
		- prog->dir_vec_y * sin(-prog->rotate_speed);
	prog->dir_vec_y = old_dir_x * sin(-prog->rotate_speed)
		+ prog->dir_vec_y * cos(-prog->rotate_speed);
	old_plane_x = prog->plane_x;
	prog->plane_x = prog->plane_x * cos(-prog->rotate_speed)
		- prog->plane_y * sin(-prog->rotate_speed);
	prog->plane_y = old_plane_x * sin(-prog->rotate_speed)
		+ prog->plane_y * cos(-prog->rotate_speed);
}

void	rotate_left(t_prog *prog)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = prog->dir_vec_x;
	prog->dir_vec_x = prog->dir_vec_x * cos(prog->rotate_speed)
		- prog->dir_vec_y * sin(prog->rotate_speed);
	prog->dir_vec_y = old_dir_x * sin(prog->rotate_speed)
		+ prog->dir_vec_y * cos(prog->rotate_speed);
	old_plane_x = prog->plane_x;
	prog->plane_x = prog->plane_x * cos(prog->rotate_speed)
		- prog->plane_y * sin(prog->rotate_speed);
	prog->plane_y = old_plane_x * sin(prog->rotate_speed)
		+ prog->plane_y * cos(prog->rotate_speed);
}

void	hook(void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (mlx_is_key_down(prog->win, MLX_KEY_W))
		move_forwards(prog);
	if (mlx_is_key_down(prog->win, MLX_KEY_A))
		move_left(prog);
	if (mlx_is_key_down(prog->win, MLX_KEY_D))
		move_right(prog);
	if (mlx_is_key_down(prog->win, MLX_KEY_S))
		move_backwards(prog);
	if (mlx_is_key_down(prog->win, MLX_KEY_RIGHT))
		rotate_right(prog);
	if (mlx_is_key_down(prog->win, MLX_KEY_LEFT))
		rotate_left(prog);
}
