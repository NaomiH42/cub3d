/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 23:36:42 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_left(t_prog *prog)
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

void	mouse_right(t_prog *prog)
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

void	mouse_hook(void *parameter)
{
	t_prog	*prog;
	int32_t	pos_x;
	int32_t	pos_y;

	prog = parameter;
	mlx_get_mouse_pos(prog->win, &pos_x, &pos_y);
	if (pos_x < 320)
		mouse_left(prog);
	else if (pos_x > 320)
		mouse_right(prog);
	mlx_set_mouse_pos(prog->win, 320, 240);
}

void	open_door(t_prog *prog, int i, int j)
{
	while (prog->map.layout[++i])
	{
		j = -1;
		while (prog->map.layout[i][++j])
		{
			if (prog->map.layout[i][j] == 'D' && ((double)i - prog->player_x
				<= 1 && (double)i - prog->player_x >= -1) && (double)j
				- (int)prog->player_y <= 1
				&& (double)j - (int)prog->player_y >= -1)
				prog->map.layout[i][j] = 'O';
			else if (prog->map.layout[i][j] == 'O' && ((double)i
			- prog->player_x <= 1 && (double)i - prog->player_x >= -1)
			&& (double)j - (int)prog->player_y <= 1
				&& (double)j - (int)prog->player_y >= -1)
				prog->map.layout[i][j] = 'D';
		}
	}
}

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;
	int		i;
	int		j;

	j = -1;
	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		mlx_delete_image(prog->win, prog->test);
		mlx_delete_image(prog->win, prog->ew);
		mlx_delete_image(prog->win, prog->nw);
		mlx_delete_image(prog->win, prog->sw);
		mlx_delete_image(prog->win, prog->ww);
		mlx_delete_image(prog->win, prog->sprites[0].tex);
		mlx_delete_image(prog->win, prog->sprites[0].tex2);
		mlx_delete_image(prog->win, prog->door);
		mlx_terminate(prog->win);
		exit(0);
	}
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{
		i = -1;
		open_door(prog, i, j);
	}
}
