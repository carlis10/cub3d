/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:36:38 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 04:43:57 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

# define WIDTH 800
# define HEIGHT 600
# define TEX_W 64
# define TEX_H 64

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
	int				floor_color;
	int				ceil_color;
	int				have_tex[4];
	int				have_floor;
	int				have_ceil;
	char			**map_lines;
	int				m_w;
	int				m_h;
	int				**map;
}			t_game;

//textures

uint32_t		get_tex_pixel(mlx_texture_t *tex, int x, int y);
void			check_texture(mlx_texture_t *tex);
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
int				check_hit(t_game *g);

//parsing

int				extract_m_b(char **f_l, int nlines, int s_i, t_game *g);
int				validate_map_block(char **map_lines, t_game *g);
int				parse_rgb_line(const char *s, int *out_color);
int				check_texture_path(const char *path);
int				parse_identifier_line(char *line, t_game *game);
int				alloc_map(t_game *game, int map_h, int map_w);
int				my_isspace(char c);
char			get_char_map(int y, int x, char **map_lines);
int				p_count(char c);
int				check_limits_map(int ny, int nx, t_game *g, char **map_lines);
int				parse_color(const char *t, int *have_color, int *dst);
int				is_texture_id(const char *t);
int				parse_tex(const char *t, t_game *game);
const char		*skip_spaces_c(const char *s);
void			init_tex_color(t_game *game);
int				parse_file(const char *filename, t_game *game);
int				count_player(t_game *g, int y, char **map_lines);
int				validate_edge_map(t_game *g, int y, int x, char **map_lines);
int				read_all_l(const char *fname, char ***out_lines, int *out_c);
void			free_lines(char **lines, int n);
void			clear_tex_paths(t_game *game);
int				has_cub_ext(const char *name);
void			free_map_lines(char **map, int h);
void			set_map_all_ones(t_game *game);
void			place_player_from_char(t_game *game, char c, int x, int y);
int				load_map_into_grid(t_game *game);
int				cleanup_and_err(char **lines, int nlines, t_game *game);

#endif
