/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:33:28 by carlos            #+#    #+#             */
/*   Updated: 2025/11/23 15:26:28 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_text(t_game *g, int x)
{
	if (g->r.side == 0)
		g->line.dist = d_aux(g->r.m_x, g->p.pos_x, g->r.step_x, g->r.ray_dir_x);
	else
		g->line.dist = d_aux(g->r.m_y, g->p.pos_y, g->r.step_y, g->r.ray_dir_y);
	if (!isfinite(g->line.dist) || g->line.dist <= 0.0)
		g->line.dist = 1e-6;
	if (g->r.side == 0)
		g->line.wall_x = g->p.pos_y + g->line.dist * g->r.ray_dir_y;
	else
		g->line.wall_x = g->p.pos_x + g->line.dist * g->r.ray_dir_x;
	g->line.wall_x -= floor(g->line.wall_x);
	draw_wall(g, x);
	g->line.line_height = (int)(HEIGHT / g->line.dist);
	g->line.draw_end = g->line.line_height / 2 + HEIGHT / 2;
	if (g->line.draw_end >= HEIGHT)
		g->line.draw_end = HEIGHT - 1;
	draw_floor_sky(g, x);
}

void	draw_first(t_game *g)
{
	if (g->r.ray_dir_x < 0)
	{
		g->r.step_x = -1;
		g->r.side_dist_x = (g->p.pos_x - g->r.m_x) * g->r.delta_x;
	}
	else
	{
		g->r.step_x = 1;
		g->r.side_dist_x = (g->r.m_x + 1.0 - g->p.pos_x) * g->r.delta_x;
	}
	if (g->r.ray_dir_y < 0)
	{
		g->r.step_y = -1;
		g->r.side_dist_y = (g->p.pos_y - g->r.m_y) * g->r.delta_y;
	}
	else
	{
		g->r.step_y = 1;
		g->r.side_dist_y = (g->r.m_y + 1.0 - g->p.pos_y) * g->r.delta_y;
	}
}

int	dda_loop(t_game *g)
{
	while (!g->r.hit)
	{
		if (g->r.side_dist_x < g->r.side_dist_y)
		{
			g->r.side_dist_x += g->r.delta_x;
			g->r.m_x += g->r.step_x;
			g->r.side = 0;
		}
		else
		{
			g->r.side_dist_y += g->r.delta_y;
			g->r.m_y += g->r.step_y;
			g->r.side = 1;
		}
		if (g->r.m_x < 0 || g->r.m_x >= g->m_w || g->r.m_y < 0 || g->r.m_y >= g->m_h)
		{
			g->r.hit = 0;
			break ;
		}
		if (g->map[g->r.m_y][g->r.m_x] > 0)
			g->r.hit = 1;
	}
	if (!g->r.hit)
		return (1);
	return (0);
}

void	cast_ray(t_game *g, int x)
{
	g->r.camerax = 2 * x / (double)WIDTH - 1;
	g->r.ray_dir_x = g->p.dir_x + g->p.plane_x * g->r.camerax;
	g->r.ray_dir_y = g->p.dir_y + g->p.plane_y * g->r.camerax;
	g->r.m_x = (int)g->p.pos_x;
	g->r.m_y = (int)g->p.pos_y;
	if (g->r.ray_dir_x == 0.0)
		g->r.delta_x = 1e30;
	else
		g->r.delta_x = fabs(1.0 / g->r.ray_dir_x);
	if (g->r.ray_dir_y == 0.0)
		g->r.delta_y = 1e30;
	else
		g->r.delta_y = fabs(1.0 / g->r.ray_dir_y);
	g->r.step_x = 0;
	g->r.step_y = 0;
	g->r.hit = 0;
	draw_first(g);
	if (dda_loop(g) != 0)
		return ;
	draw_text(g, x);
}

void	draw_scene(t_game *g)
{
	int	x;

	x = 0;
	draw_background(g);
	while (x < WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
}
