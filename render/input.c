/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:45:39 by carlos            #+#    #+#             */
/*   Updated: 2025/11/25 16:32:39 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_game *g, double m_spd)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		if (!g->map[(int)g->p.pos_y][(int)(g->p.pos_x + g->p.dir_x * m_spd)])
			g->p.pos_x += g->p.dir_x * m_spd;
		if (!g->map[(int)(g->p.pos_y + g->p.dir_y * m_spd)][(int)g->p.pos_x])
			g->p.pos_y += g->p.dir_y * m_spd;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		if (!g->map[(int)g->p.pos_y][(int)(g->p.pos_x - g->p.dir_x * m_spd)])
			g->p.pos_x -= g->p.dir_x * m_spd;
		if (!g->map[(int)(g->p.pos_y - g->p.dir_y * m_spd)][(int)g->p.pos_x])
			g->p.pos_y -= g->p.dir_y * m_spd;
	}
}

void	strafe_player(t_game *g, double m_spd)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		if (!g->map[(int)g->p.pos_y][(int)(g->p.pos_x - g->p.plane_x * m_spd)])
			g->p.pos_x -= g->p.plane_x * m_spd;
		if (!g->map[(int)(g->p.pos_y - g->p.plane_y * m_spd)][(int)g->p.pos_x])
			g->p.pos_y -= g->p.plane_y * m_spd;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		if (!g->map[(int)g->p.pos_y][(int)(g->p.pos_x + g->p.plane_x * m_spd)])
			g->p.pos_x += g->p.plane_x * m_spd;
		if (!g->map[(int)(g->p.pos_y + g->p.plane_y * m_spd)][(int)g->p.pos_x])
			g->p.pos_y += g->p.plane_y * m_spd;
	}
}

void	rotate_player(t_game *g, double r_spd)
{
	double	old_dir_x;
	double	old_planex;

	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
	{
		old_dir_x = g->p.dir_x;
		g->p.dir_x = g->p.dir_x * cos(r_spd) - g->p.dir_y * sin(r_spd);
		g->p.dir_y = old_dir_x * sin(r_spd) + g->p.dir_y * cos(r_spd);
		old_planex = g->p.plane_x;
		g->p.plane_x = g->p.plane_x * cos(r_spd) - g->p.plane_y * sin(r_spd);
		g->p.plane_y = old_planex * sin(r_spd) + g->p.plane_y * cos(r_spd);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = g->p.dir_x;
		g->p.dir_x = g->p.dir_x * cos(-r_spd) - g->p.dir_y * sin(-r_spd);
		g->p.dir_y = old_dir_x * sin(-r_spd) + g->p.dir_y * cos(-r_spd);
		old_planex = g->p.plane_x;
		g->p.plane_x = g->p.plane_x * cos(-r_spd) - g->p.plane_y * sin(-r_spd);
		g->p.plane_y = old_planex * sin(-r_spd) + g->p.plane_y * cos(-r_spd);
	}
}

void	hook(void *param)
{
	t_game	*g;
	double	m_spd;
	double	rot_spd;

	g = param;
	m_spd = 0.05;
	rot_spd = 0.03;
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	move_player(g, m_spd);
	strafe_player(g, m_spd);
	rotate_player(g, rot_spd);
	draw_scene(g);
}
