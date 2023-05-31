#include "cub3d.h"

typedef struct	m_prog
{
	void	*win;
	int		screen_w;
	int		screen_h;
	int		half_screen_w;
	int		half_screen_h;
	int		player_x;
	int		player_y;
	int		player_angle;
	int	ray_precision;
	int		w_cen;
	int		h_cen;
	int		fov;
	int		dist_proj;
	int		angle_rays;
	int		sqr_size;
	double		increm_angle;
	// char	map[7][7];
}				t_prog;

typedef struct 	m_ray
{
	double	x;
	double	y;
}				t_ray;


double	degToRad(int degrees)
{
	return ((double)(degrees * M_PI / 180));
}

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		mlx_terminate(prog->win);
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

		// printf("%f\n", prog.increm_angle);
		ray.x = prog.player_x;
		ray.y = prog.player_y;
		rayCos = cos(degToRad(rayAngle)) / prog.ray_precision;
		raySin = sin(degToRad(rayAngle)) / prog.ray_precision;
		wall = '0';
		// for (int i = 0; i < 300; i++)
		while (wall != '1')
		{
			ray.x += rayCos;
			ray.y += raySin;
			// printf("x:%d\ny:%d\n", (int)ray.x, (int)ray.y);
			// printf("%c\n", map[(int)ray.y][(int)ray.x]);
			wall = map[(int)ray.y][(int)ray.x];
			// printf("%c\n", wall);
		}
		// printf("%f", cos(degToRad(rayAngle)) / prog.r);
		// printf("%f\n", ray.x);
		distance = sqrt(pow(prog.player_x - ray.x, 2) + pow(prog.player_y - ray.y, 2));
		wallHeight = (int)(prog.half_screen_h / distance);
		// printf("%d\n", wallHeight);
		draw_line(test, rayCount, 0, rayCount, prog.half_screen_h - wallHeight, 0xFFFFFF);
		draw_line(test, rayCount, prog.half_screen_h - wallHeight, rayCount, prog.half_screen_h + wallHeight, 0x00FFFF);
		draw_line(test, rayCount, prog.half_screen_h + wallHeight, rayCount, prog.screen_h, 0xFF00FF);
		rayAngle += prog.increm_angle;
		rayCount++;
	}
}

int	main(void)
{
	t_prog prog;
	char	map[7][10] = {	"1111111111",
							"1011000001",
							"1000001001",
							"100P000001",
							"1000001001",
							"1001000001",
							"1111111111"};


	prog.screen_w = 640;
	prog.screen_h = 480;
	prog.half_screen_h = prog.screen_h / 2;
	prog.half_screen_w = prog.screen_w / 2;
	prog.player_angle = 30;
	prog.fov = 60;
	prog.player_x = 3;
	prog.player_y = 3;
	prog.dist_proj = (prog.screen_w / 2) / tan(degToRad(30));
	prog.angle_rays = prog.fov / prog.screen_w;
	prog.sqr_size = 128;
	prog.ray_precision = 64;
	prog.increm_angle = (double)prog.fov / (double)prog.screen_w;
	prog.win = mlx_init(prog.screen_w, prog.screen_h, "Test", 1);
	mlx_image_t *test = mlx_new_image(prog.win, 640, 480);
	mlx_image_to_window(prog.win, test, 0, 0);
	rayCasting(prog, map, test);
	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop(prog.win);

}
