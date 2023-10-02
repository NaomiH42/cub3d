/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 21:54:15 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line2(mlx_image_t *image, int begin_x, int begin_y, int color)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = begin_x - begin_x;
	delta_y = 480 - begin_y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = begin_x;
	pixel_y = begin_y;
	while (pixels)
	{
		mlx_put_pixel(image, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	draw_line1(mlx_image_t *image, int begin_x, int end_y, int color)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = begin_x - begin_x;
	delta_y = end_y - 0;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = begin_x;
	pixel_y = 0;
	while (pixels)
	{
		mlx_put_pixel(image, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	draw_square(mlx_image_t *image, t_prog *prog, int color)
{
	int	x;
	int	begin_x;
	int	begin_y;
	int	end_x;
	int	end_y;

	begin_x = prog->mini_x * (prog->mini_width);
	begin_y = (prog->mini_y) * (prog->mini_height);
	end_x = (prog->mini_x * prog->mini_width) + prog->mini_width;
	end_y = (prog->mini_y * prog->mini_height) + prog->mini_height;
	x = begin_y;
	while (begin_x < end_x)
	{
		x = begin_y;
		while (x < end_y)
		{
			mlx_put_pixel(image, begin_x, x, color);
			x += 1;
		}
		begin_x += 1 ;
	}
}
