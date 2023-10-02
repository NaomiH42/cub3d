/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:35 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 21:48:57 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	put_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t	*px;

	px = (uint32_t *)(img->pixels + (img->width * y + x) * sizeof(uint32_t));
	return (*px);
}

void	sprite_cast2(t_prog *prog, t_render_info *f)
{
	f->inv_det = 1.0 / (prog->plane_x
			* prog->dir_vec_y - prog->dir_vec_x * prog->plane_y);
	f->transform_x = f->inv_det * (prog->dir_vec_y
			* f->sprite_x - prog->dir_vec_x * f->sprite_y);
	f->tr_y = f->inv_det * (-prog->plane_y
			* f->sprite_x + prog->plane_x * f->sprite_y);
	f->v_ms = (int)(V_MOVE / f->tr_y);
	f->sp_sx = (int)((640 / 2)
			* (1 + f->transform_x / f->tr_y));
	f->sp_h = abs((int)(480 / f->tr_y)) / V_DIV;
	f->draw_start_y = (-f->sp_h / 2 + 480 / 2) + f->v_ms;
	if (f->draw_start_y < 0)
		f->draw_start_y = 0;
	f->draw_end_y = (f->sp_h
			/ 2 + 480 / 2) + f->v_ms;
	if (f->draw_end_y >= 480)
		f->draw_end_y = 480 - 1;
	f->sp_w = abs((int)(480 / (f->tr_y))) / U_DIV;
	f->draw_start_x = -f->sp_w / 2 + f->sp_sx;
	if (f->draw_start_x < 0)
		f->draw_start_x = 0;
	f->draw_end_x = f->sp_w / 2 + f->sp_sx;
	if (f->draw_end_x >= 640)
		f->draw_end_x = 640 - 1;
}

void	sprite_cast3(t_prog *prog, t_render_info *f)
{
	f->d = (f->y - f->v_ms) * 256 - 480 * 128
		+ f->sp_h * 128;
	f->tex_y = ((f->d * 64) / f->sp_h) / 256;
	f->tex_col = put_pixel_color(prog->sprites[0].tex,
			f->tex_x, f->tex_y);
	if ((f->tex_col & 0x00FFFFFF) != 0)
		mlx_put_pixel(prog->test, f->str, f->y, f->tex_col);
}

void	sprite_cast(t_prog *prog, t_render_info *f)
{
	f->i = -1;
	while (++f->i < 1)
	{
		f->sprite_x = prog->sprites[0].x - prog->player_x;
		f->sprite_y = prog->sprites[0].y - prog->player_y;
		sprite_cast2(prog, f);
		f->str = f->draw_start_x;
		while (++f->str < f->draw_end_x)
		{
			f->tex_x = (int)((256 * (f->str - (-f->sp_w
								/ 2 + f->sp_sx)) * 64 / f->sp_w) / 256);
			if (f->tr_y > 0 && f->str > 0 && f->str < 640 && f->tr_y
				< prog->z_buffer[f->str])
			{
				f->y = f->draw_start_y;
				while (++f->y < f->draw_end_y)
				{
					sprite_cast3(prog, f);
				}
			}
		}
	}
}

void	texture_cast(t_prog *prog, t_cast_info *info, t_render_info *f)
{
	f->y = info->draw_start - 1;
	while (++f->y < info->draw_end)
	{
		f->tex_y = (int)f->tex_pos & (64 - 1);
		f->tex_pos += f->step;
		if (info->wall_no_wall == 2)
			f->tex_col = put_pixel_color(prog->door, f->tex_x, f->tex_y);
		else if (info->side == 1)
			f->tex_col = put_pixel_color(prog->ew, f->tex_x, f->tex_y);
		else if (info->side == 2)
			f->tex_col = put_pixel_color(prog->nw, f->tex_x, f->tex_y);
		else if (info->side == 0)
			f->tex_col = put_pixel_color(prog->sw, f->tex_x, f->tex_y);
		else
			f->tex_col = put_pixel_color(prog->ww, f->tex_x, f->tex_y);
		mlx_put_pixel(prog->test, f->ray_count, f->y, f->tex_col);
	}
	draw_line1(prog->test, f->ray_count, info->draw_start,
		rgb_to_argb(prog->map.cr, prog->map.cg, prog->map.cb));
	draw_line2(prog->test, f->ray_count, info->draw_end,
		rgb_to_argb(prog->map.fr, prog->map.fg, prog->map.fb));
	prog->z_buffer[f->ray_count] = info->wall_dist;
}
