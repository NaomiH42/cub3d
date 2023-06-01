#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include "libft/libft.h"
# include "MLX42//include/MLX42/MLX42.h"
# include <stdlib.h>
# include <fcntl.h>

# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F 5
# define C 6
# define N 90

typedef struct s_coor
{
	int	x;
	int	y;
}	t_coor;

typedef struct s_map
{
	t_coor	pcoor;
	t_coor	ecoor;
	t_coor	encoor;
	char	**layout;
	char	**layouttest;
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	int		FR;
	int		FG;
	int		FB;
	int		CR;
	int		CG;
	int		CB;
}	t_map;

typedef struct	m_prog
{
	void	*win;
	int		screen_w;
	int		screen_h;
	int		half_screen_w;
	int		half_screen_h;
	float		player_x;
	float		player_y;
	int		player_angle;
	int	ray_precision;
	int		w_cen;
	int		h_cen;
	int		fov;
	int		dist_proj;
	int		angle_rays;
	int		sqr_size;
	double		increm_angle;
	mlx_image_t *test;
	int		turn_r;
	int		turn_l;
	int		go_f;
	int		go_b;
}				t_prog;

t_map	get_map_info(char *map_file, t_prog *prog);

#endif
