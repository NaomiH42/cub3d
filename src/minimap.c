/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 23:36:42 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mini_cast_render(t_prog *prog)
{
	if (prog->map.layout[prog->mini_y][prog->mini_x] == 'O')
		draw_square(prog->mini, prog, 0xFFBBBBBB);
	else
		draw_square(prog->mini, prog, 0xAAAAAAAA);
	prog->mini_x = prog->player_y;
	prog->mini_y = prog->player_x;
	draw_square(prog->mini, prog, 0xFF0000AA);
}

void	prepare_map(t_prog *prog, int *i, int *j)
{
	*i = -1;
	while (prog->map.layout[++(*i)])
	{
		*j = -1;
		while (prog->map.layout[*i][++(*j)])
		{
			if (prog->map.layout[*i][*j] == 'N'
				|| prog->map.layout[*i][*j] == 'E'
				|| prog->map.layout[*i][*j] == 'W'
				|| prog->map.layout[*i][*j] == 'S')
			{
				prog->mini_x = *j;
				prog->mini_y = *i;
				prog->map.layout[*i][*j] = '0';
			}
			if (prog->map.layout[*i][*j] == 'C')
			{
				prog->sprites[0].x = *i;
				prog->sprites[0].y = *j;
				prog->map.layout[*i][*j] = '0';
			}
		}
	}
}

void	prepare_mini(t_prog *prog, int i, int j)
{
	if (i > j)
	{
		prog->mini = mlx_new_image(prog->win, 200, 200);
		prog->mini_height = 200 / i;
		prog->mini_width = 200 / i;
	}
	else
	{
		prog->mini = mlx_new_image(prog->win, 200, 200);
		prog->mini_height = 200 / j;
		prog->mini_width = 200 / j;
	}
}

void	draw_square_main(t_main_info f, t_prog *prog, int color)
{
	int	x;
	int	begin_y;
	int	begin_x;
	int	end_x;
	int	end_y;

	begin_x = f.k;
	begin_y = f.d;
	end_x = f.k + prog->mini_width;
	end_y = f.d + prog->mini_height;
	x = begin_y;
	while (begin_x < end_x)
	{
		x = begin_y;
		while (x < end_y)
		{
			mlx_put_pixel(prog->mini, begin_x, x, color);
			x += 1;
		}
		begin_x += 1 ;
	}
}

void	draw_mini(t_main_info *f, t_prog *prog)
{
	f->i = -1;
	f->k = 0;
	f->d = 0;
	while (prog->map.layout[++f->i])
	{
		f->j = -1;
		f->k = 0;
		while (prog->map.layout[f->i][++f->j])
		{
			if (prog->map.layout[f->i][f->j] == '0')
				draw_square_main(*f, prog, 0xAAAAAAAA);
			else if (prog->map.layout[f->i][f->j] == '1')
				draw_square_main(*f, prog, 0xFFFFFFAA);
			else if (prog->map.layout[f->i][f->j] == 'D')
				draw_square_main(*f, prog, 0xFFBBBBBB);
			f->k += prog->mini_width;
		}
		f->d += prog->mini_height;
	}
}
