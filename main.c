#include "cub3d.h"

double	deg_to_rad(int degrees)
{
	return ((double)(degrees * M_PI / 180));
}

void	move_forwards(t_prog *prog)
{
	if (prog->map.layout[(int)(prog->player_x
			+ prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == '0'
		|| prog->map.layout[(int)(prog->player_x
			+ prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 'O')
		prog->player_x += prog->dir_vec_x * prog->move_speed / 10;
	if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ prog->dir_vec_y * prog->move_speed)] == '0'
		|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		+ prog->dir_vec_y * prog->move_speed)] == 'O')
		prog->player_y += prog->dir_vec_y * prog->move_speed / 10;
}

void	move_backwards(t_prog *prog)
{
	if (prog->map.layout[(int)(prog->player_x - prog->dir_vec_x
			* prog->move_speed)][(int)prog->player_y] == '0'
		|| prog->map.layout[(int)(prog->player_x - prog->dir_vec_x
		* prog->move_speed)][(int)prog->player_y] == 'O')
		prog->player_x -= prog->dir_vec_x * prog->move_speed / 10;
	if (prog->map.layout[(int)prog->player_x][(int)(prog->player_y
		- prog->dir_vec_y * prog->move_speed)] == '0'
		|| prog->map.layout[(int)prog->player_x][(int)(prog->player_y
			- prog->dir_vec_y * prog->move_speed)] == 'O')
		prog->player_y -= prog->dir_vec_y * prog->move_speed / 10;
}

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
	draw_line1(prog->test, f->ray_count, info->draw_start, 0xFFFFFF);
	draw_line2(prog->test, f->ray_count, info->draw_end, 0xFF00FF);
	prog->z_buffer[f->ray_count] = info->wall_dist;
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

void	change_sprite(t_prog *prog)
{
	mlx_image_t	*temp;

	temp = prog->sprites[0].tex;
	prog->sprites[0].tex = prog->sprites[0].tex2;
	prog->sprites[0].tex2 = temp;
}

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

void	prog_init(t_prog *prog)
{
	prog->screen_w = 640;
	prog->screen_h = 480;
	prog->map = get_map_info("./map.cub", prog);
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
	door = mlx_load_png("./pics/door1.png");
	if (!door)
		exit(0);
	prog->door = mlx_texture_to_image(prog->win, door);
	mlx_delete_texture(door);
	mlx_delete_texture(bar);
	mlx_delete_texture(bar2);
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
	mlx_set_cursor_mode(prog.win, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(prog.win, hook, &prog);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop_hook(prog.win, frame_creator, &prog);
	mlx_loop_hook(prog.win, mouse_hook, &prog);
	mlx_loop(prog.win);
}
