/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:45:39 by carlos            #+#    #+#             */
/*   Updated: 2025/11/17 16:17:02 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void move_player(t_game *g, double moveSpeed)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		if (!g->map[(int)g->p.posY][(int)(g->p.posX + g->p.dirX * moveSpeed)])
			g->p.posX += g->p.dirX * moveSpeed;
		if (!g->map[(int)(g->p.posY + g->p.dirY * moveSpeed)][(int)g->p.posX])
			g->p.posY += g->p.dirY * moveSpeed;
		printf("player x:%f\n player y:%f", g->p.posX, g->p.posY);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		if (!g->map[(int)g->p.posY][(int)(g->p.posX - g->p.dirX * moveSpeed)])
			g->p.posX -= g->p.dirX * moveSpeed;
		if (!g->map[(int)(g->p.posY - g->p.dirY * moveSpeed)][(int)g->p.posX])
			g->p.posY -= g->p.dirY * moveSpeed;
		printf("player x:%f\n player y:%f", g->p.posX, g->p.posY);
	}
}

void strafe_player(t_game *g, double moveSpeed)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		if (!g->map[(int)g->p.posY][(int)(g->p.posX - g->p.planeX * moveSpeed)])
			g->p.posX -= g->p.planeX * moveSpeed;
		if (!g->map[(int)(g->p.posY - g->p.planeY * moveSpeed)][(int)g->p.posX])
			g->p.posY -= g->p.planeY * moveSpeed;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		if (!g->map[(int)g->p.posY][(int)(g->p.posX + g->p.planeX * moveSpeed)])
			g->p.posX += g->p.planeX * moveSpeed;
		if (!g->map[(int)(g->p.posY + g->p.planeY * moveSpeed)][(int)g->p.posX])
			g->p.posY += g->p.planeY * moveSpeed;
	}
}

void rotate_player(t_game *g, double rotSpeed)
{
	double oldDirX, oldPlaneX;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
	{
		oldDirX = g->p.dirX;
		g->p.dirX = g->p.dirX * cos(rotSpeed) - g->p.dirY * sin(rotSpeed);
		g->p.dirY = oldDirX * sin(rotSpeed) + g->p.dirY * cos(rotSpeed);
		oldPlaneX = g->p.planeX;
		g->p.planeX = g->p.planeX * cos(rotSpeed) - g->p.planeY * sin(rotSpeed);
		g->p.planeY = oldPlaneX * sin(rotSpeed) + g->p.planeY * cos(rotSpeed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
	{
		oldDirX = g->p.dirX;
		g->p.dirX = g->p.dirX * cos(-rotSpeed) - g->p.dirY * sin(-rotSpeed);
		g->p.dirY = oldDirX * sin(-rotSpeed) + g->p.dirY * cos(-rotSpeed);
		oldPlaneX = g->p.planeX;
		g->p.planeX = g->p.planeX * cos(-rotSpeed) - g->p.planeY * sin(-rotSpeed);
		g->p.planeY = oldPlaneX * sin(-rotSpeed) + g->p.planeY * cos(-rotSpeed);
	}
}

void hook(void *param)
{
	t_game *g = param;
	double moveSpeed = 0.05;
	double rotSpeed = 0.03;

	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	move_player(g, moveSpeed);
	strafe_player(g, moveSpeed);
	rotate_player(g, rotSpeed);
	draw_scene(g);
}
