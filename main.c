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
		if (prog->map.layout[(int)(prog->player_x + prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == '0'
			|| prog->map.layout[(int)(prog->player_x + prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 'O')
			prog->player_x += prog->dir_vec_x * prog->move_speed / 10;
		if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y + prog->dir_vec_y * prog->move_speed)] == '0'
			|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y + prog->dir_vec_y * prog->move_speed)] == 'O')
			prog->player_y += prog->dir_vec_y * prog->move_speed / 10;
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_A))
	{
		double x = -prog->dir_vec_y;
		double y = prog->dir_vec_x;
		if (prog->map.layout[(int)(prog->player_x + x * prog->move_speed)][(int)prog->player_y] == '0'
			|| prog->map.layout[(int)(prog->player_x + x * prog->move_speed)][(int)prog->player_y] == 'O')
			prog->player_x += x * prog->move_speed / 10;
		if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y + y * prog->move_speed)] == '0'
			|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y + y * prog->move_speed)] == 'O')
			prog->player_y += y * prog->move_speed / 10;
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_D))
	{
		double x = prog->dir_vec_y;
		double y = -prog->dir_vec_x;
		if (prog->map.layout[(int)(prog->player_x + x * prog->move_speed)][(int)prog->player_y] == '0'
			|| prog->map.layout[(int)(prog->player_x + x * prog->move_speed)][(int)prog->player_y] == 'O')
			prog->player_x += x * prog->move_speed / 10;
		if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y + y * prog->move_speed)] == '0'
			|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y + y * prog->move_speed)] == 'O')
			prog->player_y += y * prog->move_speed / 10;
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_S))
	{
		if (prog->map.layout[(int)(prog->player_x - prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == '0'
			|| prog->map.layout[(int)(prog->player_x - prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 'O')
			prog->player_x -= prog->dir_vec_x * prog->move_speed / 10;
		if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y - prog->dir_vec_y * prog->move_speed)] == '0'
			|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y - prog->dir_vec_y * prog->move_speed)] == 'O')
			prog->player_y -= prog->dir_vec_y * prog->move_speed / 10;
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_RIGHT))
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(-prog->rotate_speed) - prog->dir_vec_y * sin(-prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(-prog->rotate_speed) + prog->dir_vec_y * cos(-prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(-prog->rotate_speed) - prog->plane_y * sin(-prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(-prog->rotate_speed) + prog->plane_y * cos(-prog->rotate_speed);
	}
	if (mlx_is_key_down(prog->win, MLX_KEY_LEFT))
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(prog->rotate_speed) - prog->dir_vec_y * sin(prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(prog->rotate_speed) + prog->dir_vec_y * cos(prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(prog->rotate_speed) - prog->plane_y * sin(prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(prog->rotate_speed) + prog->plane_y * cos(prog->rotate_speed);
	}
}

void	mouse_hook(void *parameter)
{
	t_prog	*prog;

	prog = parameter;

	int32_t pos_x;
	int32_t pos_y;
	mlx_get_mouse_pos(prog->win, &pos_x, &pos_y);
	if (pos_x < 320)
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(prog->rotate_speed) - prog->dir_vec_y * sin(prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(prog->rotate_speed) + prog->dir_vec_y * cos(prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(prog->rotate_speed) - prog->plane_y * sin(prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(prog->rotate_speed) + prog->plane_y * cos(prog->rotate_speed);
	
	}
	else if (pos_x > 320)
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(-prog->rotate_speed) - prog->dir_vec_y * sin(-prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(-prog->rotate_speed) + prog->dir_vec_y * cos(-prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(-prog->rotate_speed) - prog->plane_y * sin(-prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(-prog->rotate_speed) + prog->plane_y * cos(-prog->rotate_speed);
	}
	mlx_set_mouse_pos(prog->win, 320, 240);	
}

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_terminate(prog->win);
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{
		int i = 0;
		while (prog->map.layout[i])
		{
			int j = 0;
			while (prog->map.layout[i][j])
			{
				if (prog->map.layout[i][j] == 'D' && ((double)i - prog->player_x <= 1 && (double)i - prog->player_x >= -1) && (double)j - (int)prog->player_y <= 1
					&& (double)j - (int)prog->player_y >= -1)
				{
					printf("%d %d\n", i, j);
					printf("%f %f\n", prog->player_x, prog->player_y);
					prog->map.layout[i][j] = 'O';
				}
				else if (prog->map.layout[i][j] == 'O' && ((double)i - prog->player_x <= 1 && (double)i - prog->player_x >= -1) && (double)j - (int)prog->player_y <= 1
					&& (double)j - (int)prog->player_y >= -1)
					prog->map.layout[i][j] = 'D';

				j++;
			}
			i++;
		}
	}
}


void draw_square(mlx_image_t *image, int beginX, int beginY, int endX, int endY, int color)
{
	int x = beginY;
	int y = 0;
	while (beginX < endX)
	{
		x = beginY;
		while (x < endY)
		{	
			mlx_put_pixel(image, beginX, x, color);
			x += 1;
		}
		beginX += 1 ;
	}
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

void	ray_casting2(t_prog *prog)
{
	t_cast_info		info;
	t_ray			ray;
	t_render_info	f;

	f.ray_count = 0;
	while (f.ray_count < prog->screen_w)
	{
		info.camera = 2 * f.ray_count / (double)prog->screen_w - 1;
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
				info.wall_no_wall = 1;
			else if (prog->map.layout[info.map_x][info.map_y] == 'D')
				info.wall_no_wall = 2;
		}
		if (info.side == 0)
			info.wall_dist = info.side_dist_x - info.dist_move_x;
		else
			info.wall_dist = info.side_dist_y - info.dist_move_y;
		if (info.side == 0 && prog->player_x > info.map_x)
			info.side = 2;
		if (info.side == 1 && prog->player_y > info.map_y)
			info.side = 3;
		info.line_height = (int)(prog->screen_h / info.wall_dist);
		info.draw_start = -info.line_height / 2 + prog->screen_h / 2;
		if (info.draw_start < 0)
			info.draw_start = 0;
		info.draw_end = info.line_height / 2 + prog->screen_h / 2;
		if (info.draw_end >= prog->screen_h)
			info.draw_end = prog->screen_h - 1;
		if (info.side == 0 || info.side == 2)
			f.wall_x = prog->player_y + info.wall_dist * ray.y;
		else
			f.wall_x = prog->player_x + info.wall_dist * ray.x;
		f.wall_x -= floor(f.wall_x);
		f.tex_x = (int)(f.wall_x * (double)64);
		if (info.side == 0 && prog->dir_vec_x > 0)
			f.tex_x = 64 - f.tex_x - 1;
		if (info.side == 1 && prog->dir_vec_y < 0)
			f.tex_x = 64 - f.tex_x - 1;
		f.step = 1.0 * 64 / info.line_height;
		f.tex_pos = (info.draw_start - prog->screen_h / 2 + info.line_height / 2) * f.step;
		f.y = info.draw_start - 1;
		while (++f.y < info.draw_end)
		{
			f.tex_y = (int)f.tex_pos & (64 - 1);
			f.tex_pos += f.step;
			if (info.wall_no_wall == 2)
				f.tex_col = put_pixel_color(prog->door, f.tex_x, f.tex_y);
			else if (info.side == 1)
				f.tex_col = put_pixel_color(prog->ew, f.tex_x, f.tex_y);
			else if (info.side == 2)
				f.tex_col = put_pixel_color(prog->nw, f.tex_x, f.tex_y);
			else if (info.side == 0)
				f.tex_col = put_pixel_color(prog->sw, f.tex_x, f.tex_y);
			else
				f.tex_col = put_pixel_color(prog->ww, f.tex_x, f.tex_y);
			mlx_put_pixel(prog->test, f.ray_count, f.y, f.tex_col);
		}
		draw_line(prog->test, f.ray_count, 0, f.ray_count, info.draw_start, 0xFFFFFF);
		draw_line(prog->test, f.ray_count, info.draw_end, f.ray_count, prog->screen_h, 0xFF00FF);
		prog->z_buffer[f.ray_count] = info.wall_dist;
		f.ray_count++;
	}
	f.i = -1;
	while (++f.i < 1)
	{
		f.sprite_x = prog->sprites[0].x - prog->player_x;
		f.sprite_y = prog->sprites[0].y - prog->player_y;

		f.inv_det = 1.0 / (prog->plane_x * prog->dir_vec_y - prog->dir_vec_x * prog->plane_y);

		f.transform_x = f.inv_det * (prog->dir_vec_y * f.sprite_x - prog->dir_vec_x * f.sprite_y);
		f.transform_y = f.inv_det * (-prog->plane_y * f.sprite_x + prog->plane_x * f.sprite_y);


		f.v_move_screen = (int)(v_move / f.transform_y);

		f.sprite_screen_x = (int)((640 / 2) * (1 + f.transform_x / f.transform_y));
		
		f.sprite_height = abs((int)(480 / f.transform_y)) / v_div;
		
		f.draw_start_y = (-f.sprite_height / 2 + 480 / 2) + f.v_move_screen;
		if (f.draw_start_y < 0)
			f.draw_start_y = 0;
		f.draw_end_y = (f.sprite_height / 2 + 480 /2) + f.v_move_screen;
		if (f.draw_end_y >= 480)
			f.draw_end_y = 480 - 1;

		f.sprite_width = abs((int)(480 / (f.transform_y))) / u_div;

		f.draw_start_x = -f.sprite_width / 2 + f.sprite_screen_x;
		if (f.draw_start_x < 0)
			f.draw_start_x = 0;
		f.draw_end_x = f.sprite_width / 2 + f.sprite_screen_x;
		if (f.draw_end_x >= 640)
			f.draw_end_x = 640 - 1;
		f.stripe = f.draw_start_x;
		while (++f.stripe < f.draw_end_x)
		{
			f.tex_x = (int)((256 * (f.stripe - (-f.sprite_width / 2 + f.sprite_screen_x)) * 64 / f.sprite_width) / 256);
			if (f.transform_y > 0 && f.stripe > 0 && f.stripe < 640 && f.transform_y < prog->z_buffer[f.stripe])
			{
				f.y = f.draw_start_y;
				while (++f.y < f.draw_end_y)
				{
					f.d = (f.y-f.v_move_screen) * 256 - 480 * 128 + f.sprite_height * 128;
					f.tex_y = ((f.d * 64) / f.sprite_height) / 256;
					f.tex_col = put_pixel_color(prog->sprites[0].tex, f.tex_x ,f.tex_y);
					if((f.tex_col & 0x00FFFFFF) != 0)
						mlx_put_pixel(prog->test, f.stripe, f.y, f.tex_col);
				}
			}
		}
	}	
	if (prog->map.layout[prog->mini_y][prog->mini_x] == 'O')		
		draw_square(prog->mini, prog->mini_x * (prog->mini_width) ,(prog->mini_y) * (prog->mini_height),  (prog->mini_x * prog->mini_width) + prog->mini_width, (prog->mini_y * prog->mini_height) + prog->mini_height, 0xFFBBBBBB);
	else
		draw_square(prog->mini, prog->mini_x * (prog->mini_width) ,(prog->mini_y) * (prog->mini_height),  (prog->mini_x * prog->mini_width) + prog->mini_width, (prog->mini_y * prog->mini_height) + prog->mini_height, 0xAAAAAAAA);
	prog->mini_x = prog->player_y;
	prog->mini_y = prog->player_x;
	draw_square(prog->mini, prog->mini_x * (prog->mini_width) ,(prog->mini_y) * (prog->mini_height),  (prog->mini_x * prog->mini_width) + prog->mini_width, (prog->mini_y * prog->mini_height) + prog->mini_height, 0xFF0000AA);

}

void	change_sprite(t_prog *prog)
{
	mlx_image_t	*temp;

	printf("AAA");
	temp = prog->sprites[0].tex;
	prog->sprites[0].tex = prog->sprites[0].tex2;
	prog->sprites[0].tex2 = temp;
}

void	frame_creator(void *param)
{
	t_prog			*prog;
	static int		i;
	static float	j;
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

void prog_init(t_prog *prog)
{
	prog->screen_w = 640;
	prog->screen_h = 480;
	prog->map = get_map_info("./map.cub", prog);
	prog->move_speed = 0.5;
	prog->rotate_speed = 0.03;
	prog->win = mlx_init(prog->screen_w, prog->screen_h, "Test", 1);
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
	prog->nw = mlx_texture_to_image(prog->win, nw);
	prog->sw = mlx_texture_to_image(prog->win, sw);
	prog->ew = mlx_texture_to_image(prog->win, ew);
	prog->ww = mlx_texture_to_image(prog->win, ww);
}

void	load_sprites(t_prog *prog)
{
	mlx_texture_t	*bar;
	mlx_texture_t	*bar2;
	mlx_texture_t	*door;

	bar = mlx_load_png("./pics/cat1.png");
	bar2 = mlx_load_png("./pics/cat2.png");
	prog->sprites[0].tex = mlx_texture_to_image(prog->win, bar);
	prog->sprites[0].tex2 = mlx_texture_to_image(prog->win, bar2);
	door = mlx_load_png("./pics/door1.png");
	prog->door = mlx_texture_to_image(prog->win, door);
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

void	draw_mini(t_main_info *f, t_prog *prog)
{
	f->i = -1;
	f->k = 0;
	f->d = 0;
	while (prog->map.layout[++f->i])
	{
		f->j = 0;
		f->k = 0;
		while (prog->map.layout[f->i][++f->j])
		{
			if (prog->map.layout[f->i][f->j] == '0')
				draw_square(prog->mini, f->k, f->d, f->k
					+ prog->mini_width, f->d + prog->mini_height, 0xAAAAAAAA);
			else if (prog->map.layout[f->i][f->j] == '1')
				draw_square(prog->mini, f->k, f->d, f->k
					+ prog->mini_width, f->d + prog->mini_height, 0xFFFFFFAA);
			else if (prog->map.layout[f->i][f->j] == 'D')
				draw_square(prog->mini, f->k, f->d, f->k
					+ prog->mini_width, f->d + prog->mini_height, 0xFFBBBBBB);
			f->k += prog->mini_width;
		}
		f->d += prog->mini_height;
	}
}

int	main(void)
{
	t_prog		prog;
	t_main_info	info;

	prog_init(&prog);
	prepare_map(&prog, &info.i, &info.j);
	prepare_mini(&prog, info.i, info.j);
	draw_mini(&info, &prog);
	load_sprites(&prog);
	mlx_image_to_window(prog.win, prog.mini, 0, 0);
	load_walls(&prog);
	mlx_loop_hook(prog.win, hook, &prog);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop_hook(prog.win, frame_creator, &prog);
	mlx_loop_hook(prog.win, mouse_hook, &prog);
	mlx_loop(prog.win);
}
