#include "cub3d.h"
#define tex_h 64
#define tex_w 64



typedef struct 	m_ray
{
	double	x;
	double	y;
}				t_ray;

double	degToRad(int degrees)
{
	return ((double)(degrees * M_PI / 180));
}


void	hook(void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (mlx_is_key_down(prog->win, MLX_KEY_W))
	{
		if (prog->map.layout[(int)(prog->player_x + prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == '0')
			prog->player_x += prog->dir_vec_x * prog->move_speed / 10;
		if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y + prog->dir_vec_y * prog->move_speed)] == '0')
			prog->player_y += prog->dir_vec_y * prog->move_speed / 10;
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_S))
	{
		if (prog->map.layout[(int)(prog->player_x - prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == '0')
			prog->player_x -= prog->dir_vec_x * prog->move_speed / 10;
		if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y - prog->dir_vec_y * prog->move_speed)] == '0')
			prog->player_y -= prog->dir_vec_y * prog->move_speed / 10;
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_D))
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(-prog->rotate_speed) - prog->dir_vec_y * sin(-prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(-prog->rotate_speed) + prog->dir_vec_y * cos(-prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(-prog->rotate_speed) - prog->plane_y * sin(-prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(-prog->rotate_speed) + prog->plane_y * cos(-prog->rotate_speed);
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_A))
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(prog->rotate_speed) - prog->dir_vec_y * sin(prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(prog->rotate_speed) + prog->dir_vec_y * cos(prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(prog->rotate_speed) - prog->plane_y * sin(prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(prog->rotate_speed) + prog->plane_y * cos(prog->rotate_speed);
	}
}

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_terminate(prog->win);

}

void draw_line(mlx_image_t *image, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX;
	double	deltaY;
	int		pixels;
	double	pixelX;
	double	pixelY;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_put_pixel(image, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

uint32_t put_pixel_color(mlx_image_t *img, int x, int y)
{
	uint32_t *px;

	px = (uint32_t *)(img->pixels + (img->width * y + x) * sizeof(uint32_t));
	return (*px);
}

void	ray_casting2(t_prog *prog)//, int map [24][24], mlx_image_t *test)
{
	int	ray_count;
	t_cast_info	info;
	t_ray	ray;

	ray_count = 0;
	while (ray_count < prog->screen_w)
	{
		info.camera = 2 * ray_count / (double)prog->screen_w - 1;
		ray.x = prog->dir_vec_x + prog->plane_x * info.camera;
		ray.y = prog->dir_vec_y + prog->plane_y * info.camera;
		if (ray.x == 0)
			info.dist_move_x = 1e30;
		else
			info.dist_move_x = 1 / ray.x;
		if (info.dist_move_x < 0)
				info.dist_move_x *= -1;
		if (ray.y == 0)
			info.dist_move_y = 1e30;
		else
			info.dist_move_y = 1 / ray.y;
		if (info.dist_move_y < 0)
				info.dist_move_y *= -1;
		info.map_x = (int)prog->player_x;
		info.map_y = (int)prog->player_y;
		info.wall_no_wall = 0;
		if (ray.x < 0)
		{
			info.step_x = -1;
			info.side_dist_x = (prog->player_x - info.map_x) * info.dist_move_x;
		}
		else
		{
			info.step_x = 1;
			info.side_dist_x = (info.map_x + 1.0 - prog->player_x) * info.dist_move_x;
		}
		if (ray.y < 0)
		{
			info.step_y = -1;
			info.side_dist_y = (prog->player_y - info.map_y) * info.dist_move_y;
		}
		else
		{
			info.step_y = 1;
			info.side_dist_y = (info.map_y + 1.0 - prog->player_y) * info.dist_move_y;
		}
		while (info.wall_no_wall == 0)
		{
			if (info.side_dist_x < info.side_dist_y)
			{
				info.side_dist_x += info.dist_move_x;
				info.map_x += info.step_x;
				info.side = 0;
			}
			else
			{
				info.side_dist_y += info.dist_move_y;
				info.map_y += info.step_y;
				info.side = 1;
			}
			if (prog->map.layout[info.map_x][info.map_y] == '1')
			{
				info.wall_no_wall = 1;
				// if (info.side == 0 && prog->player_x > info.map_x)
				// 	info.side = 2;
			}
		}
		if (info.side == 0)
			info.wall_dist = info.side_dist_x - info.dist_move_x;
		else
			info.wall_dist = info.side_dist_y - info.dist_move_y;
		// if (info.side == 0 && prog->player_x > info.map_x)
		// 	info.side = 2;
		// if (info.side == 1 && prog->player_y > info.map_y)
		// 	info.side = 3;
		info.line_height = (int)(prog->screen_h / info.wall_dist);
		info.draw_start = -info.line_height / 2 + prog->screen_h / 2;
		if (info.draw_start < 0)
			info.draw_start = 0;
		info.draw_end = info.line_height / 2 + prog->screen_h / 2;
		if (info.draw_end >= prog->screen_h)
			info.draw_end = prog->screen_h - 1;

		char tex_num = prog->map.layout[info.map_x][info.map_y];

		double wall_x;
		if (info.side == 0)
			wall_x = prog->player_x + info.wall_dist * ray.y;
		else
			wall_x = prog->player_y + info.wall_dist * ray.x;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * (double)64);
		if (info.side == 0 && prog->dir_vec_x > 0)
			tex_x = 64 - tex_x - 1;
		if (info.side == 1 && prog->dir_vec_y < 0)
			tex_x = 64 - tex_x - 1;
		double step = 1.0 * 64 / info.line_height;
		double tex_pos = (info.draw_start - prog->screen_h / 2 + info.line_height / 2) * step;
		for (int y = 0; y < info.draw_end; y++)
		{
			int tex_y = (int)tex_pos & (64 - 1);
			tex_pos += step;
			mlx_image_t *aaa = mlx_texture_to_image(prog->win, prog->nw);
			mlx_put_pixel(prog->test, ray_count, y, put_pixel_color(aaa, tex_x, tex_y));
		}
		// mlx_texture_to_image(prog->win, prog->nw);
		// draw_line(prog->test, ray_count, 0, ray_count, info.draw_start, 0xFFFFFF);
		// if (info.side == 1)
		// 	draw_line(prog->test, ray_count, info.draw_start,  ray_count, info.draw_end, 0x9900FFFF);
		// else if (info.side == 2)
		// 	draw_line(prog->test, ray_count, info.draw_start,  ray_count, info.draw_end, 0x9999FFFF);
		// else if (info.side == 0)
		// 	draw_line(prog->test, ray_count, info.draw_start,  ray_count, info.draw_end, 0x0099FFFF);
		// else
		// 	draw_line(prog->test, ray_count, info.draw_start,  ray_count, info.draw_end, 0x999999FF);
		// draw_line(prog->test, ray_count, info.draw_end, ray_count, prog->screen_h, 0xFF00FF);

		ray_count++;
	}
}

// void	move_f(t_prog *prog, float *j, int worldMap[24][24])
// {
// 	if (*j == 10)
// 	{
// 		prog->go_f = 0;
// 		*j = 0;
// 		return ;
// 	}
// 	if (worldMap[(int)(prog->player_x + prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 0)
// 			prog->player_x += (prog->dir_vec_x * prog->move_speed) / 10;
// 	if (worldMap[(int)prog->player_x][(int)(prog->player_y + prog->dir_vec_y * prog->move_speed)] == 0)
// 			prog->player_y += (prog->dir_vec_y * prog->move_speed) / 10;
// 	*j++;
// }

void	frame_creator(void *param)
{
	t_prog *prog;
	prog = param;
	int i = 0;
	static float j;
	ray_casting2(prog);
	printf("PlaneX:%f\nPlaneY:%f\nDirX:%f\nDirY:%f\nX:%f\nY:%f\n", prog->plane_x, prog->plane_y, prog->dir_vec_x, prog->dir_vec_y, prog->player_x, prog->player_y);

}

int	main(void)
{
	t_prog prog;
	prog.screen_w = 640;
	prog.screen_h = 480;

	prog.map = get_map_info("./map.cub", &prog);
	prog.move_speed = 0.5;
	prog.rotate_speed = 0.03;
	prog.win = mlx_init(prog.screen_w, prog.screen_h, "Test", 1);
	prog.test = mlx_new_image(prog.win, 640, 480);
	mlx_image_to_window(prog.win, prog.test, 0, 0);
	prog.nw = mlx_load_png("./pics/bluestone.png");
	printf("%f\n%f\n%f\n%f\n", prog.player_x, prog.player_y, prog.dir_vec_x, prog.dir_vec_y);
	// printf("NO:%s\nSO:%s\nWE:%s\nEA:%s\nF:%d, %d, %d\nC:%d, %d, %d\n", prog.map.no_t, prog.map.so_t, prog.map.we_t, prog.map.ea_t, prog.map.FR, prog.map.FG, prog.map.FB, prog.map.CR, prog.map.CG, prog.map.CB);
	int i = 0;
	int j;
	while (prog.map.layout[i])
	{
		j = 0;
		while (prog.map.layout[i][j])
		{
			printf("%c", prog.map.layout[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	prog.nw = mlx_load_png("./pics/greystone.png");
	mlx_loop_hook(prog.win, hook, &prog);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop_hook(prog.win, frame_creator, &prog);
	mlx_loop(prog.win);

}
