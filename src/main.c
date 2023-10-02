/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:46:58 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/02 21:48:03 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting_init_val(t_cast_info *info, t_ray *ray
	, t_prog *prog, t_render_info *f)
{
	info->camera = 2 * f->ray_count / (double)prog->screen_w - 1;
	ray->x = prog->dir_vec_x + prog->plane_x * info->camera;
	ray->y = prog->dir_vec_y + prog->plane_y * info->camera;
	if (ray->x == 0)
		info->dist_move_x = 1e30;
	else
		info->dist_move_x = 1 / ray->x;
	if (info->dist_move_x < 0)
		info->dist_move_x *= -1;
	if (ray->y == 0)
		info->dist_move_y = 1e30;
	else
		info->dist_move_y = 1 / ray->y;
	if (info->dist_move_y < 0)
		info->dist_move_y *= -1;
	info->map_x = (int)prog->player_x;
	info->map_y = (int)prog->player_y;
	info->wall_no_wall = 0;
}

void	change_sprite(t_prog *prog)
{
	mlx_image_t	*temp;

	temp = prog->sprites[0].tex;
	prog->sprites[0].tex = prog->sprites[0].tex2;
	prog->sprites[0].tex2 = temp;
}

int	main(int argc, char **argv)
{
	t_prog		prog;
	t_main_info	info;

	if (argc != 2)
		error_msg("Incorrect number of arguments.");
	prog_init(&prog, argv[1]);
	prepare_map(&prog, &info.i, &info.j);
	prepare_mini(&prog, info.i, info.j);
	draw_mini(&info, &prog);
	printf("r%d g%d b%d\n", prog.map.cr, prog.map.cg, prog.map.cb);
	printf("%d", rgb_to_argb(prog.map.cr, prog.map.cg, prog.map.cb));
	load_sprites(&prog);
	mlx_image_to_window(prog.win, prog.mini, 0, 0);
	load_walls(&prog);
	mlx_set_cursor_mode(prog.win, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(prog.win, hook, &prog);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop_hook(prog.win, frame_creator, &prog);
	mlx_loop_hook(prog.win, mouse_hook, &prog);
	mlx_loop(prog.win);
}
