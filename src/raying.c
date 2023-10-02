/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raying.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 23:36:42 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting_ray_set(t_cast_info *info, t_ray *ray
	, t_prog *prog)
{
	if (ray->x < 0)
	{
		info->step_x = -1;
		info->side_dist_x = (prog->player_x - info->map_x) * info->dist_move_x;
	}
	else
	{
		info->step_x = 1;
		info->side_dist_x = (info->map_x + 1.0 - prog->player_x)
			* info->dist_move_x;
	}
	if (ray->y < 0)
	{
		info->step_y = -1;
		info->side_dist_y = (prog->player_y - info->map_y) * info->dist_move_y;
	}
	else
	{
		info->step_y = 1;
		info->side_dist_y = (info->map_y + 1.0 - prog->player_y)
			* info->dist_move_y;
	}
}

void	cast_rays(t_cast_info *info, t_prog *prog)
{
	if (info->side_dist_x < info->side_dist_y)
	{
		info->side_dist_x += info->dist_move_x;
		info->map_x += info->step_x;
		info->side = 0;
	}
	else
	{
		info->side_dist_y += info->dist_move_y;
		info->map_y += info->step_y;
		info->side = 1;
	}
	if (prog->map.layout[info->map_x][info->map_y] == '1')
		info->wall_no_wall = 1;
	else if (prog->map.layout[info->map_x][info->map_y] == 'D')
		info->wall_no_wall = 2;
}

void	assign_dir(t_cast_info *info, t_prog *prog)
{
	if (info->side == 0)
		info->wall_dist = info->side_dist_x - info->dist_move_x;
	else
		info->wall_dist = info->side_dist_y - info->dist_move_y;
	if (info->side == 0 && prog->player_x > info->map_x)
		info->side = 2;
	if (info->side == 1 && prog->player_y > info->map_y)
		info->side = 3;
	info->line_height = (int)(prog->screen_h / info->wall_dist);
	info->draw_start = -info->line_height / 2 + prog->screen_h / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	info->draw_end = info->line_height / 2 + prog->screen_h / 2;
	if (info->draw_end >= prog->screen_h)
		info->draw_end = prog->screen_h - 1;
}

void	cast_texture(t_cast_info *info, t_render_info *f, t_prog *prog
	, t_ray *ray)
{
	if (info->side == 0 || info->side == 2)
		f->wall_x = prog->player_y + info->wall_dist * ray->y;
	else
		f->wall_x = prog->player_x + info->wall_dist * ray->x;
	f->wall_x -= floor(f->wall_x);
	f->tex_x = (int)(f->wall_x * (double)64);
	if (info->side == 0 && prog->dir_vec_x > 0)
		f->tex_x = 64 - f->tex_x - 1;
	if (info->side == 1 && prog->dir_vec_y < 0)
		f->tex_x = 64 - f->tex_x - 1;
	f->step = 1.0 * 64 / info->line_height;
	f->tex_pos = (info->draw_start - prog->screen_h
			/ 2 + info->line_height / 2) * f->step;
}

void	ray_casting2(t_prog *prog)
{
	t_cast_info		info;
	t_ray			ray;
	t_render_info	f;

	f.ray_count = 0;
	while (f.ray_count < prog->screen_w)
	{
		ray_casting_init_val(&info, &ray, prog, &f);
		ray_casting_ray_set(&info, &ray, prog);
		while (info.wall_no_wall == 0)
			cast_rays(&info, prog);
		assign_dir(&info, prog);
		cast_texture(&info, &f, prog, &ray);
		texture_cast(prog, &info, &f);
		f.ray_count++;
	}
	sprite_cast(prog, &f);
	mini_cast_render(prog);
}
