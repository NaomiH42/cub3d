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
	void		*win;
	int			screen_w;
	int			screen_h;
	double		player_x;
	double		player_y;
	double		move_speed;
	double		rotate_speed;
	double		dir_vec_x;
	double		dir_vec_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
	mlx_image_t *test;;
	t_map		map;
	mlx_texture_t *nw;
	mlx_texture_t *sw;
	mlx_texture_t *ew;
	mlx_texture_t *ww;
}				t_prog;

typedef struct	m_cast_info
{
	double	camera;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	dist_move_x;
	double	dist_move_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		wall_no_wall;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_cast_info;

t_map	get_map_info(char *map_file, t_prog *prog);

#endif
