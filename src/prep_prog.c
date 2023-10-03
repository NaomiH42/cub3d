/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/03 11:47:31 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	frame_creator(void *param)
{
	t_prog			*prog;
	static int		i;
	static double	old;
	double			time;

	prog = param;
	if (i == 0)
	{
		prog->frame = 0;
		i = 1;
		old = 0;
	}
	time = mlx_get_time();
	if (time - old >= (double)1 / 120)
	{
		prog->frame += 1;
		if (prog->frame % 30 == 0)
			change_sprite(prog);
		if (prog->frame == 120)
			prog->frame = 0;
		old = mlx_get_time();
		ray_casting2(prog);
	}
}

void	prog_init(t_prog *prog, char *map)
{
	prog->screen_w = 640;
	prog->screen_h = 480;
	prog->map = get_map_info(map, prog);
	prog->move_speed = 0.5;
	prog->rotate_speed = 0.03;
	prog->win = mlx_init(prog->screen_w, prog->screen_h, "cub3d", 1);
	if (!prog->win)
		exit(0);
	prog->test = mlx_new_image(prog->win, 640, 480);
	mlx_image_to_window(prog->win, prog->test, 0, 0);
}

void	load_walls(t_prog *prog)
{
	mlx_texture_t	*nw;
	mlx_texture_t	*sw;
	mlx_texture_t	*ew;
	mlx_texture_t	*ww;

	nw = mlx_load_png(prog->map.no_t);
	sw = mlx_load_png(prog->map.so_t);
	ew = mlx_load_png(prog->map.ea_t);
	ww = mlx_load_png(prog->map.we_t);
	if (!nw || !sw || !ew || !ww)
		exit(0);
	prog->nw = mlx_texture_to_image(prog->win, nw);
	prog->sw = mlx_texture_to_image(prog->win, sw);
	prog->ew = mlx_texture_to_image(prog->win, ew);
	prog->ww = mlx_texture_to_image(prog->win, ww);
	mlx_delete_texture(nw);
	mlx_delete_texture(sw);
	mlx_delete_texture(ew);
	mlx_delete_texture(ww);
}

void	load_sprites(t_prog *prog)
{
	mlx_texture_t	*bar;
	mlx_texture_t	*bar2;
	mlx_texture_t	*door;

	bar = mlx_load_png("./pics/cat1.png");
	bar2 = mlx_load_png("./pics/cat2.png");
	if (!bar || ! bar2)
		exit(0);
	prog->sprites[0].tex = mlx_texture_to_image(prog->win, bar);
	prog->sprites[0].tex2 = mlx_texture_to_image(prog->win, bar2);
	door = mlx_load_png("./pics/door.png");
	if (!door)
		exit(0);
	prog->door = mlx_texture_to_image(prog->win, door);
	mlx_delete_texture(door);
	mlx_delete_texture(bar);
	mlx_delete_texture(bar2);
}
