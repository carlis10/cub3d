/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:36:38 by carlos            #+#    #+#             */
/*   Updated: 2025/11/22 13:42:00 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WIDTH 800
# define HEIGHT 600
# define TEX_W 64
# define TEX_H 64
# define M_W 10
# define M_H 10

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_ray
{
	double	camerax;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	int		m_x;
	int		m_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;

}			t_ray;

typedef struct s_line
{
	double	dist;
	double	wall_x;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_line;

typedef struct s_texture
{
	mlx_texture_t	*tex;
	uint32_t		color;
	int				tex_x;
	int				tex_y;
	int				height;
	int				width;

}				t_texture;

typedef struct s_game
{
	t_player		p;
	t_ray			r;
	t_texture		t;
	t_line			line;
	mlx_image_t		*img;
	mlx_t			*mlx;
	mlx_texture_t	*wall_tex[4];
	int				map[M_H][M_W];
}			t_game;

//textures

uint32_t		get_tex_pixel(mlx_texture_t *tex, int x, int y);
void			check_texture(mlx_texture_t *tex, const char *name);
void			draw_background(t_game *g);
mlx_texture_t	*w_t(t_game *g, int side, double ray_dir_x, double ray_dir_y);

//raycast

void			draw_wall(t_game *g, int x);

void			draw_floor_sky(t_game *g, int x);

//input

void			hook(void *param);
void			rotate_player(t_game *g, double rotSpeed);
void			strafe_player(t_game *g, double moveSpeed);
void			move_player(t_game *g, double moveSpeed);

//draw

void			cast_ray(t_game *g, int x);
void			draw_scene(t_game *g);
double			d_aux(int map, double pos, int step, double ray_dir);

#endif
