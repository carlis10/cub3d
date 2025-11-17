/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:36:38 by carlos            #+#    #+#             */
/*   Updated: 2025/11/17 16:13:52 by carlos           ###   ########.fr       */
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
# define MAP_W 10
# define MAP_H 10

typedef struct s_player
{
	double posX, posY;
	double dirX, dirY;
	double planeX, planeY;
} t_player;

typedef struct s_game
{
	t_player p;
	mlx_image_t *img;
	mlx_t *mlx;
	mlx_texture_t *wallTex[4];
	int map[MAP_H][MAP_W];
} t_game;

//textures

uint32_t get_tex_pixel(mlx_texture_t *tex, int x, int y);
void check_texture(mlx_texture_t *tex, const char *name);
void draw_background(t_game *g);
mlx_texture_t *choose_wall_texture(t_game *g, int side, double rayDirX, double rayDirY);

//raycast

void draw_wall(t_game *g, int x, double perpWallDist, int side,
	double wallX, double rayDirX, double rayDirY);

void draw_floor_sky(t_game *g, int x, int drawEnd, double perpWallDist);

//input

void hook(void *param);
void rotate_player(t_game *g, double rotSpeed);
void strafe_player(t_game *g, double moveSpeed);
void move_player(t_game *g, double moveSpeed);

//draw

void cast_ray(t_game *g, int x);
void draw_scene(t_game *g);

#endif
