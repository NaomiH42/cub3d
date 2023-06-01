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

void	move_forward(t_prog *prog)
{
	double	player_cos;
	double	player_sin;
	double	new_x;
	double	new_y;
	char	map[7][10] = {	"1111111111",
							"1001000001",
							"1000000001",
							"1100001001",
							"1000000001",
							"1001000001",
							"1111111111"};

	player_cos = cos(degToRad(prog->player_angle)) * 1;
	player_sin = sin(degToRad(prog->player_angle)) * 1;

	new_x = prog->player_x + player_cos;
	new_y = prog->player_y + player_sin;
	if (map[(int)new_y][(int)new_x] == '0')
	{
		prog->player_x = new_x;
		prog->player_y = new_y;
	}
}

void	move_backward(t_prog *prog)
{
	double	player_cos;
	double	player_sin;
	double	new_x;
	double	new_y;
	char	map[7][10] = {	"1111111111",
							"1001000001",
							"1000000001",
							"1100001001",
							"1000000001",
							"1001000001",
							"1111111111"};

	// player_cos = cos(degToRad(prog->player_angle)) * 1;
	// player_sin = sin(degToRad(prog->player_angle)) * 1;
	new_x = prog->player_x - player_cos;
	new_y = prog->player_y - player_sin;
	if (map[(int)new_y][(int)new_x] == '0')
	{
		prog->player_x = new_x;
		prog->player_y = new_y;
	}
}

void	turn_right(t_prog *prog)
{
	int i = 0;
	double time = mlx_get_time();
	while (i < 90)
	{
		if (mlx_get_time() - time > 1)
		{
			prog->player_angle += 1;
			i++;
		}
	}
}

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_terminate(prog->win);
	if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		prog->go_f = 1;//move_forward(prog);
	if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		prog->go_b = 1;//move_backward(prog);
	else if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		prog->turn_r = 1;//;turn_right(prog);//prog->player_angle += 90;
	else if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
		prog->turn_l = 1;//prog->player_angle -= 90;

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

void	rayCasting(t_prog prog, char map[7][10], mlx_image_t *test)
{
	double		rayAngle;
	int		rayCount;
	t_ray	ray;
	double	rayCos;
	double	raySin;
	char		wall;
	double		distance;
	int		wallHeight;

	ray.x = prog.player_x;
	ray.y = prog.player_y;

	rayCount = 0;
	rayAngle = prog.player_angle - prog.fov;
	while (rayCount < prog.screen_w)
	{
		ray.x = prog.player_x;
		ray.y = prog.player_y;
		rayCos = cos(degToRad(rayAngle)) / prog.ray_precision;
		raySin = sin(degToRad(rayAngle)) / prog.ray_precision;
		wall = '0';
		while (wall != '1')
		{
			ray.x += rayCos;
			ray.y += raySin;
			wall = map[(int)ray.y][(int)ray.x];
		}
		distance = sqrt(pow(prog.player_x - ray.x, 2) + pow(prog.player_y - ray.y, 2));
		// distance = distance * cos(degToRad((prog.player_angle - rayAngle) * 0.1));
		wallHeight = (int)(prog.half_screen_h / distance);
		draw_line(test, rayCount, 0, rayCount, prog.half_screen_h - wallHeight, 0xFFFFFF);
		draw_line(test, rayCount, prog.half_screen_h - wallHeight, rayCount, prog.half_screen_h + wallHeight, 0x9900FFFF);
		draw_line(test, rayCount, prog.half_screen_h + wallHeight, rayCount, prog.screen_h, 0xFF00FF);
		rayAngle += prog.increm_angle;
		rayCount++;
	}
}

void	move_b(t_prog *prog, float *j)
{
	char	map[7][10] = {	"1111111111",
							"1101000001",
							"1000000001",
							"1100001001",
							"1000000001",
							"1001000001",
							"1111111111"};

	if (prog->player_angle == 20)
	{
		if (map[(int)prog->player_y][(int)prog->player_x - 1] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_x = round(prog->player_x);
			prog->go_b = 0;
			*j = 0;
			return ;
		}
		prog->player_x -= 0.1;
		*j += 0.1;
	}
	if (prog->player_angle == 110)
	{
		if (map[(int)prog->player_y - 1][(int)prog->player_x] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_y = round(prog->player_y);
			prog->go_b = 0;
			*j = 0;
			return ;
		}
		prog->player_y -= 0.1;
		*j += 0.1;
	}
	if (prog->player_angle == -70)
	{
		if (map[(int)prog->player_y + 1][(int)prog->player_x] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_y = round(prog->player_y);
			prog->go_b = 0;
			*j = 0;
			return ;
		}
		prog->player_y += 0.1;
		*j += 0.1;
	}
	if (prog->player_angle == 200)
	{
		if (map[(int)prog->player_y][(int)prog->player_x + 1] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_x = round(prog->player_x);
			prog->go_b = 0;
			*j = 0;
			return ;
		}
		prog->player_x += 0.1;
		*j += 0.1;
	}
}

void	move_f(t_prog *prog, float *j)
{
	char	map[7][10] = {	"1111111111",
							"1101000001",
							"1000000001",
							"1100001001",
							"1000000001",
							"1001000001",
							"1111111111"};

	if (prog->player_angle == 20)
	{
		if (map[(int)prog->player_y][(int)prog->player_x + 1] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_x = round(prog->player_x);
			prog->go_f = 0;
			*j = 0;
			return ;
		}
		prog->player_x += 0.1;
		*j += 0.1;
	}
	if (prog->player_angle == 110)
	{
		if (map[(int)prog->player_y + 1][(int)prog->player_x] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_y = round(prog->player_y);
			prog->go_f = 0;
			*j = 0;
			return ;
		}
		prog->player_y += 0.1;
		*j += 0.1;
	}
	if (prog->player_angle == -70)
	{
		if (map[(int)prog->player_y - 1][(int)prog->player_x] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_y = round(prog->player_y);
			prog->go_f = 0;
			*j = 0;
			return ;
		}
		prog->player_y -= 0.1;
		*j += 0.1;
	}
	if (prog->player_angle == 200)
	{
		if (map[(int)prog->player_y][(int)prog->player_x - 1] == '1')
		{
			prog->go_f = 0;
			return ;
		}
		if (*j >= 1)
		{
			prog->player_x = round(prog->player_x);
			prog->go_f = 0;
			*j = 0;
			return ;
		}
		prog->player_x -= 0.1;
		*j += 0.1;
	}
}
void	turn_r(t_prog *prog, float *j)
{
	if (*j == 30)
	{
		if (prog->player_angle == 290)
			prog->player_angle = -70;
		prog->turn_r = 0;
		*j = 0;
	}
	else
	{
		prog->player_angle += 3;
		*j += 1;
	}
}

void	turn_l(t_prog *prog, float *j)
{
	if (*j == 30)
	{
		if (prog->player_angle == -160)
			prog->player_angle = 200;
		prog->turn_l = 0;
		*j = 0;
	}
	else
	{
		prog->player_angle -= 3;
		*j += 1;
	}
}

void	frame_creator(void *param)
{
	t_prog *prog;
	prog = param;
	int i = 0;
	static float j;
	char	map[7][10] = {	"1111111111",
							"1101000001",
							"1000000001",
							"1100001001",
							"1000000001",
							"1001000001",
							"1111111111"};
	if (prog->turn_r == 1)
		turn_r(prog, &j);
	if (prog->turn_l == 1)
		turn_l(prog, &j);
	if (prog->go_b == 1)
		move_b(prog, &j);
	if (prog->go_f == 1)
		move_f(prog, &j);
	rayCasting(*prog, map, prog->test);
	printf("Angle:%d, X:%f\nY:%f\n", prog->player_angle, prog->player_x, prog->player_y);
	int l = 0;
	int k;
	while (l < 7)
	{
		k = 0;
		while (k < 10)
		{
			if (l == prog->player_y && k == prog->player_x)
				printf("P");
			else
				printf("%c", map[l][k]);
			k++;
		}
		l++;
		printf("\n");
	}
	// mlx_delete_image(prog->win, test);

}

int	main(void)
{
	t_prog prog;
	t_map	map_i;
	char	map[7][10] = {	"1111111111",
							"3003000004",
							"3000000004",
							"3300003004",
							"3000000004",
							"3003000004",
							"2222222222"};

	prog.screen_w = 640;
	prog.screen_h = 480;
	prog.half_screen_h = prog.screen_h / 2;
	prog.half_screen_w = prog.screen_w / 2;
	prog.player_angle = 20;
	prog.fov = 60;
	prog.player_x = 3;
	prog.player_y = 3;
	prog.dist_proj = (prog.screen_w / 2) / tan(degToRad(30));
	prog.angle_rays = prog.fov / prog.screen_w;
	prog.sqr_size = 128;
	prog.ray_precision = 64;
	prog.increm_angle = (double)prog.fov / (double)prog.screen_w;
	prog.turn_r = 0;
	prog.turn_l = 0;
	prog.go_f = 0;
	prog.win = mlx_init(prog.screen_w, prog.screen_h, "Test", 1);
	prog.test = mlx_new_image(prog.win, 640, 480);
	mlx_image_to_window(prog.win, prog.test, 0, 0);

	// map_i = get_map_info("./map.cub", &prog);
	// printf("NO:%s\nSO:%s\nWE:%s\nEA:%s\nF:%d, %d, %d\nC:%d, %d, %d\n", map_i.no_t, map_i.so_t, map_i.we_t, map_i.ea_t, map_i.FR, map_i.FG, map_i.FB, map_i.CR, map_i.CG, map_i.CB);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop_hook(prog.win, frame_creator, &prog);
	mlx_loop(prog.win);

}
