/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehasalu <ehasalu@42prague.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:18:24 by ehasalu           #+#    #+#             */
/*   Updated: 2023/10/03 00:00:57 by ehasalu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F 5
# define C 6
# define N 90
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0
# define TEX_H 64
# define TEX_W 64

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
	int		fr;
	int		fg;
	int		fb;
	int		cr;
	int		cg;
	int		cb;
}	t_map;

typedef struct m_sprite
{
	int			x;
	int			y;
	mlx_image_t	*tex;
	mlx_image_t	*tex2;
}				t_sprite;

typedef struct m_prog
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
	mlx_image_t	*test;
	t_map		map;
	mlx_image_t	*nw;
	mlx_image_t	*sw;
	mlx_image_t	*ew;
	mlx_image_t	*ww;
	mlx_image_t	*mini;
	int			mini_x;
	int			mini_y;
	int			mini_width;
	int			mini_height;
	double		z_buffer[640];
	t_sprite	sprites[1];
	mlx_image_t	*door;
	int			frame;
	int			door_x;
	int			door_y;
}				t_prog;

typedef struct m_ray
{
	double	x;
	double	y;
}				t_ray;

typedef struct m_check_info
{
	int	i;
	int	l;
	int	check;
	int	max_i;
	int	*max_l;
}				t_check_info;

typedef struct m_render_info
{
	int			ray_count;
	int			tex_x;
	int			i;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			tex_y;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		tr_y;
	int			v_ms;
	int			sp_sx;
	int			sp_h;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_end_x;
	int			draw_start_x;
	int			sp_w;
	int			sprite;
	int			str;
	int			y;
	int			d;
	uint32_t	tex_col;
}				t_render_info;

typedef struct m_main_info
{
	int	j;
	int	i;
	int	k;
	int	d;
}				t_main_info;

typedef struct m_cast_info
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

//casting
uint32_t	put_pixel_color(mlx_image_t *img, int x, int y);
void		sprite_cast2(t_prog *prog, t_render_info *f);
void		sprite_cast3(t_prog *prog, t_render_info *f);
void		sprite_cast(t_prog *prog, t_render_info *f);
void		texture_cast(t_prog *prog, t_cast_info *info, t_render_info *f);

//controls
void		mouse_left(t_prog *prog);
void		mouse_right(t_prog *prog);
void		mouse_hook(void *parameter);
void		open_door(t_prog *prog, int i, int j);
void		hooks(mlx_key_data_t key, void *parameter);

//controls2
void		move_left(t_prog *prog);
void		move_right(t_prog *prog);
void		rotate_right(t_prog *prog);
void		rotate_left(t_prog *prog);

void		hook(void *parameter);

//controls3
double		deg_to_rad(int degrees);
int			rgb_to_argb(int r, int g, int b);
void		move_forwards(t_prog *prog);
void		move_backwards(t_prog *prog);

//drawing
void		draw_line2(mlx_image_t *image, int begin_x, int begin_y, int color);
void		draw_line1(mlx_image_t *image, int begin_x, int end_y, int color);
void		draw_square(mlx_image_t *image, t_prog *prog, int color);

//main
void		ray_casting_init_val(t_cast_info *info, t_ray *ray,
				t_prog *prog, t_render_info *f);
void		change_sprite(t_prog *prog);

//map
void		get_value_color_c(char *line, t_map *map);
void		get_value_color_f(char *line, t_map *map);
int			check_value(char *line, t_map *map);
void		get_map_info2(char **line, t_map *map1, int *fd, int *checker);
t_map		get_map_info(char *map_file, t_prog *prog);

//map2
void		set_start_values(char symbol, int i, int l, t_prog *prog);
void		set_max_l(int **max_l, char **la, int l, int i);
void		check_map_req(char **la, t_prog *prog);
char		*ft_charjoin(char *s1, char s2);
char		*get_value_texture(char *line);

//map3
void		error_msg(char *msg);
void		map_test(char **la, int m[], int n);
void		check_corr_symbols2(char **la, int i, int l, t_check_info info);
void		check_corr_symbols(char **la, t_check_info info);
void		set_start_values2(t_prog *p,
				double vec_x, double vec_y, double plane_x);

//minimap
void		mini_cast_render(t_prog *prog);
void		prepare_map(t_prog *prog, int *i, int *j);
void		prepare_mini(t_prog *prog, int i, int j);
void		draw_square_main(t_main_info f, t_prog *prog, int color);
void		draw_mini(t_main_info *f, t_prog *prog);

//prep_prog
void		frame_creator(void *param);
void		prog_init(t_prog *prog, char *map);
void		load_walls(t_prog *prog);
void		load_sprites(t_prog *prog);

//raying
void		ray_casting_ray_set(t_cast_info *info, t_ray *ray,
				t_prog *prog);
void		cast_rays(t_cast_info *info, t_prog *prog);
void		assign_dir(t_cast_info *info, t_prog *prog);
void		cast_texture(t_cast_info *info, t_render_info *f, t_prog *prog,
				t_ray *ray);
void		ray_casting2(t_prog *prog);

#endif
