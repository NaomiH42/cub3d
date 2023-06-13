#include "cub3d.h"



typedef struct 	m_ray
{
	double	x;
	double	y;
}				t_ray;

double	degToRad(int degrees)
{
	return ((double)(degrees * M_PI / 180));
}

// void	move_forward(t_prog *prog)
// {
// 	double	player_cos;
// 	double	player_sin;
// 	double	new_x;
// 	double	new_y;
// 	char	map[7][10] = {	"1111111111",
// 							"1001000001",
// 							"1000000001",
// 							"1100001001",
// 							"1000000001",
// 							"1001000001",
// 							"1111111111"};

// 	player_cos = cos(degToRad(prog->player_angle)) * 1;
// 	player_sin = sin(degToRad(prog->player_angle)) * 1;

// 	new_x = prog->player_x + player_cos;
// 	new_y = prog->player_y + player_sin;
// 	if (map[(int)new_y][(int)new_x] == '0')
// 	{
// 		prog->player_x = new_x;
// 		prog->player_y = new_y;
// 	}
// }

// void	move_backward(t_prog *prog)
// {
// 	double	player_cos;
// 	double	player_sin;
// 	double	new_x;
// 	double	new_y;
// 	char	map[7][10] = {	"1111111111",
// 							"1001000001",
// 							"1000000001",
// 							"1100001001",
// 							"1000000001",
// 							"1001000001",
// 							"1111111111"};

// 	// player_cos = cos(degToRad(prog->player_angle)) * 1;
// 	// player_sin = sin(degToRad(prog->player_angle)) * 1;
// 	new_x = prog->player_x - player_cos;
// 	new_y = prog->player_y - player_sin;
// 	if (map[(int)new_y][(int)new_x] == '0')
// 	{
// 		prog->player_x = new_x;
// 		prog->player_y = new_y;
// 	}
// }

// void	turn_right(t_prog *prog)
// {
// 	int i = 0;
// 	double time = mlx_get_time();
// 	while (i < 90)
// 	{
// 		if (mlx_get_time() - time > 1)
// 		{
// 			prog->player_angle += 1;
// 			i++;
// 		}
// 	}
// }

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;
	int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_terminate(prog->win);
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
	{
		if (worldMap[(int)(prog->player_x + prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 0)
			prog->player_x += prog->dir_vec_x * prog->move_speed;
		if (worldMap[(int)prog->player_x][(int)(prog->player_y + prog->dir_vec_y * prog->move_speed)] == 0)
			prog->player_y += prog->dir_vec_y * prog->move_speed;
		//prog->go_f = 1;//move_forward(prog);
	}
	else if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
	{	if (worldMap[(int)(prog->player_x - prog->dir_vec_x * prog->move_speed)][(int)prog->player_y] == 0)
			prog->player_x -= prog->dir_vec_x * prog->move_speed;
		if (worldMap[(int)prog->player_x][(int)(prog->player_y - prog->dir_vec_y * prog->move_speed)] == 0)
			prog->player_y -= prog->dir_vec_y * prog->move_speed;
	}	//move_backward(prog);
	else if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(-prog->rotate_speed) - prog->dir_vec_y * sin(-prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(-prog->rotate_speed) + prog->dir_vec_y * cos(-prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(-prog->rotate_speed) - prog->plane_y * sin(-prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(-prog->rotate_speed) + prog->plane_y * cos(-prog->rotate_speed);
	}
	else if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
	{
		double	old_dir_x = prog->dir_vec_x;
		prog->dir_vec_x = prog->dir_vec_x * cos(prog->rotate_speed) - prog->dir_vec_y * sin(prog->rotate_speed);
		prog->dir_vec_y = old_dir_x * sin(prog->rotate_speed) + prog->dir_vec_y * cos(prog->rotate_speed);
 		double old_plane_x = prog->plane_x;
		prog->plane_x = prog->plane_x * cos(prog->rotate_speed) - prog->plane_y * sin(prog->rotate_speed);
		prog->plane_y = old_plane_x * sin(prog->rotate_speed) + prog->plane_y * cos(prog->rotate_speed);
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

// void	rayCasting(t_prog prog, char map[7][10], mlx_image_t *test)
// {
// 	double		rayAngle;
// 	int		rayCount;
// 	t_ray	ray;
// 	double	rayCos;
// 	double	raySin;
// 	char		wall;
// 	double		distance;
// 	int		wallHeight;

// 	ray.x = prog.player_x;
// 	ray.y = prog.player_y;

// 	rayCount = 0;
// 	rayAngle = prog.player_angle - prog.fov;
// 	while (rayCount < prog.screen_w)
// 	{
// 		ray.x = prog.player_x;
// 		ray.y = prog.player_y;
// 		rayCos = cos(degToRad(rayAngle)) / prog.ray_precision;
// 		raySin = sin(degToRad(rayAngle)) / prog.ray_precision;
// 		wall = '0';
// 		while (wall != '1')
// 		{
// 			ray.x += rayCos;
// 			ray.y += raySin;
// 			wall = map[(int)ray.y][(int)ray.x];
// 		}
// 		distance = sqrt(pow(prog.player_x - ray.x, 2) + pow(prog.player_y - ray.y, 2));
// 		// distance = distance * cos(degToRad((prog.player_angle - rayAngle) * 0.1));
// 		wallHeight = (int)(prog.half_screen_h / distance);
// 		draw_line(test, rayCount, 0, rayCount, prog.half_screen_h - wallHeight, 0xFFFFFF);
// 		draw_line(test, rayCount, prog.half_screen_h - wallHeight, rayCount, prog.half_screen_h + wallHeight, 0x9900FFFF);
// 		draw_line(test, rayCount, prog.half_screen_h + wallHeight, rayCount, prog.screen_h, 0xFF00FF);
// 		rayAngle += prog.increm_angle;
// 		rayCount++;
// 	}
// }

// void	move_b(t_prog *prog, float *j)
// {
// 	char	map[7][10] = {	"1111111111",
// 							"1101000001",
// 							"1000000001",
// 							"1100001001",
// 							"1000000001",
// 							"1001000001",
// 							"1111111111"};

// 	if (prog->player_angle == 20)
// 	{
// 		if (map[(int)prog->player_y][(int)prog->player_x - 1] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_x = round(prog->player_x);
// 			prog->go_b = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_x -= 0.1;
// 		*j += 0.1;
// 	}
// 	if (prog->player_angle == 110)
// 	{
// 		if (map[(int)prog->player_y - 1][(int)prog->player_x] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_y = round(prog->player_y);
// 			prog->go_b = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_y -= 0.1;
// 		*j += 0.1;
// 	}
// 	if (prog->player_angle == -70)
// 	{
// 		if (map[(int)prog->player_y + 1][(int)prog->player_x] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_y = round(prog->player_y);
// 			prog->go_b = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_y += 0.1;
// 		*j += 0.1;
// 	}
// 	if (prog->player_angle == 200)
// 	{
// 		if (map[(int)prog->player_y][(int)prog->player_x + 1] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_x = round(prog->player_x);
// 			prog->go_b = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_x += 0.1;
// 		*j += 0.1;
// 	}
// }

// void	move_f(t_prog *prog, float *j)
// {
// 	char	map[7][10] = {	"1111111111",
// 							"1101000001",
// 							"1000000001",
// 							"1100001001",
// 							"1000000001",
// 							"1001000001",
// 							"1111111111"};

// 	if (prog->player_angle == 20)
// 	{
// 		if (map[(int)prog->player_y][(int)prog->player_x + 1] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_x = round(prog->player_x);
// 			prog->go_f = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_x += 0.1;
// 		*j += 0.1;
// 	}
// 	if (prog->player_angle == 110)
// 	{
// 		if (map[(int)prog->player_y + 1][(int)prog->player_x] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_y = round(prog->player_y);
// 			prog->go_f = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_y += 0.1;
// 		*j += 0.1;
// 	}
// 	if (prog->player_angle == -70)
// 	{
// 		if (map[(int)prog->player_y - 1][(int)prog->player_x] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_y = round(prog->player_y);
// 			prog->go_f = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_y -= 0.1;
// 		*j += 0.1;
// 	}
// 	if (prog->player_angle == 200)
// 	{
// 		if (map[(int)prog->player_y][(int)prog->player_x - 1] == '1')
// 		{
// 			prog->go_f = 0;
// 			return ;
// 		}
// 		if (*j >= 1)
// 		{
// 			prog->player_x = round(prog->player_x);
// 			prog->go_f = 0;
// 			*j = 0;
// 			return ;
// 		}
// 		prog->player_x -= 0.1;
// 		*j += 0.1;
// 	}
// }
// void	turn_r(t_prog *prog, float *j)
// {
// 	if (*j == 30)
// 	{
// 		if (prog->player_angle == 290)
// 			prog->player_angle = -70;
// 		prog->turn_r = 0;
// 		*j = 0;
// 	}
// 	else
// 	{
// 		prog->player_angle += 3;
// 		*j += 1;
// 	}
// }

// void	turn_l(t_prog *prog, float *j)
// {
// 	if (*j == 30)
// 	{
// 		if (prog->player_angle == -160)
// 			prog->player_angle = 200;
// 		prog->turn_l = 0;
// 		*j = 0;
// 	}
// 	else
// 	{
// 		prog->player_angle -= 3;
// 		*j += 1;
// 	}
// }



void	ray_casting2(t_prog *prog, int map [24][24], mlx_image_t *test)
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
			if (map[info.map_x][info.map_y] > 0)
				info.wall_no_wall = 1;
		}
		if (info.side == 0)
			info.wall_dist = info.side_dist_x - info.dist_move_x;
		else
			info.wall_dist = info.side_dist_y - info.dist_move_y;

		info.line_height = (int)(prog->screen_h / info.wall_dist);
		info.draw_start = -info.line_height / 2 + prog->screen_h / 2;
		if (info.draw_start < 0)
			info.draw_start = 0;
		info.draw_end = info.line_height / 2 + prog->screen_h / 2;
		if (info.draw_end >= prog->screen_h)
			info.draw_end = prog->screen_h - 1;

		draw_line(test, ray_count, 0, ray_count, info.draw_start, 0xFFFFFF);
		draw_line(test, ray_count, info.draw_start,  ray_count, info.draw_end, 0x9900FFFF);
		draw_line(test, ray_count, info.draw_end, ray_count, prog->screen_h, 0xFF00FF);

		ray_count++;
	}
}

void	frame_creator(void *param)
{
	t_prog *prog;
	prog = param;
	int i = 0;
	static float j;
	int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	char	map[7][10] = {	"1111111111",
							"1000000001",
							"1000000001",
							"1100000001",
							"1000000001",
							"1000000001",
							"1111111111"};
	// if (prog->turn_r == 1)
	// 	turn_r(prog, &j);
	// if (prog->turn_l == 1)
	// 	turn_l(prog, &j);
	// if (prog->go_b == 1)
	// 	move_b(prog, &j);
	// if (prog->go_f == 1)
	// 	move_f(prog, &j);
	ray_casting2(prog, worldMap, prog->test);
	// printf("Angle:%d, X:%f\nY:%f\n", prog->player_angle, prog->player_x, prog->player_y);
	// int l = 0;
	// int k;
	// while (l < 7)
	// {
	// 	k = 0;
	// 	while (k < 10)
	// 	{
	// 		if (l == prog->player_y && k == prog->player_x)
	// 			printf("P");
	// 		else
	// 			printf("%c", map[l][k]);
	// 		k++;
	// 	}
	// 	l++;
	// 	printf("\n");
	// }
	// mlx_delete_image(prog->win, test);

}

int	main(void)
{
	t_prog prog;
	t_map	map_i;
		int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	char	map[7][10] = {	"1111111111",
							"3003000004",
							"3000000004",
							"3300003004",
							"3000000004",
							"3003000004",
							"2222222222"};

	prog.screen_w = 640;
	prog.screen_h = 480;
	prog.player_x = 22;
	prog.player_y = 20;
	prog.plane_x = 0;
	prog.plane_y = 0.66;
	prog.dir_vec_x = -1;
	prog.dir_vec_y = 0;
	prog.move_speed = 1;
	prog.rotate_speed = 1;
	prog.win = mlx_init(prog.screen_w, prog.screen_h, "Test", 1);
	prog.test = mlx_new_image(prog.win, 640, 480);
	mlx_image_to_window(prog.win, prog.test, 0, 0);

	// rc(&prog, map, prog.test);
	// ray_casting2(&prog, worldMap, prog.test);
	// map_i = get_map_info("./map.cub", &prog);
	// printf("NO:%s\nSO:%s\nWE:%s\nEA:%s\nF:%d, %d, %d\nC:%d, %d, %d\n", map_i.no_t, map_i.so_t, map_i.we_t, map_i.ea_t, map_i.FR, map_i.FG, map_i.FB, map_i.CR, map_i.CG, map_i.CB);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop_hook(prog.win, frame_creator, &prog);
	mlx_loop(prog.win);

}
