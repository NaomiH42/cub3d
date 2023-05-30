#include <math.h>
#include <stdio.h>
#include "libft/libft.h"
#include "MLX42//include/MLX42/MLX42.h"


typedef struct	m_prog
{
	void	*win;
	int		w_proj;
	int		h_proj;
	int		w_cen;
	int		h_cen;
	int		fov;
	int		dist_proj;
	int		angle_rays;
	int		sqr_size;
}				t_prog;

void	hooks(mlx_key_data_t key, void *parameter)
{
	t_prog	*prog;

	prog = parameter;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	{
		mlx_terminate(prog->win);
	}
}

int	main(void)
{
	t_prog prog;
	char	map[3][3] = {	"111",
							"101",
							"1P1"};


	prog.w_proj = 640;
	prog.h_proj = 420;
	prog.w_cen = prog.w_proj / 2;
	prog.h_cen = prog.h_proj / 2;
	prog.fov = 60;
	prog.dist_proj = (prog.w_proj / 2) / tan(30. * 3.14 / 180);
	prog.angle_rays = prog.fov / prog.w_proj;
	prog.sqr_size = 128;
	prog.win = mlx_init(prog.w_proj, prog.h_proj, "Test", 1);

	mlx_key_hook(prog.win, hooks, &prog);
	mlx_loop(prog.win);

}
