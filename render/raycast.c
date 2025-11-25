/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:35:21 by carlos            #+#    #+#             */
/*   Updated: 2025/11/25 16:31:20 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_texture(t_game *g, int x)
{
	int	y;
	int	tx;
	int	ty;
	int	d;

	y = g->line.draw_start;
	g->t.tex = w_t(g, g->r.side, g->r.ray_dir_x, g->r.ray_dir_y);
	g->t.width = g->t.tex->width;
	g->t.height = g->t.tex->height;
	while (y <= g->line.draw_end)
	{
		d = y * 256 - HEIGHT * 128 + g->line.line_height * 128;
		g->t.tex_y = ((d * g->t.height) / g->line.line_height) / 256;
		tx = ((g->t.tex_x % g->t.width) + g->t.width) % g->t.width;
		ty = ((g->t.tex_y % g->t.height) + g->t.height) % g->t.height;
		g->t.color = get_tex_pixel(g->t.tex, tx, ty);
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			mlx_put_pixel(g->img, x, y, g->t.color);
		y++;
	}
}

void	draw_wall(t_game *g, int x)
{
	if (g->line.dist <= 0.0 || !isfinite(g->line.dist))
		return ;
	g->line.line_height = (int)(HEIGHT / g->line.dist);
	g->line.draw_start = -g->line.line_height / 2 + HEIGHT / 2;
	if (g->line.draw_start < 0)
		g->line.draw_start = 0;
	g->line.draw_end = g->line.line_height / 2 + HEIGHT / 2;
	if (g->line.draw_end >= HEIGHT)
		g->line.draw_end = HEIGHT - 1;
	g->t.tex_x = (int)(g->line.wall_x * TEX_W);
	if (g->r.side == 0 && g->r.ray_dir_x > 0)
		g->t.tex_x = TEX_W - g->t.tex_x - 1;
	if (g->r.side == 1 && g->r.ray_dir_y < 0)
		g->t.tex_x = TEX_W - g->t.tex_x - 1;
	draw_texture(g, x);
}

void	draw_floor_sky(t_game *g, int x)
{
	int		y;
	double	current_dist;
	int		sky_y;

	y = g->line.draw_end + 1;
	if (g->line.dist <= 0.0 || !isfinite(g->line.dist))
		return ;
	while (y < HEIGHT)
	{
		current_dist = HEIGHT / (2.0 * y - HEIGHT);
		if (!isfinite(current_dist) || current_dist <= 0.0)
			continue ;
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			mlx_put_pixel(g->img, x, y, g->floor_color);
			sky_y = HEIGHT - y;
			if (sky_y >= 0 && sky_y < HEIGHT)
				mlx_put_pixel(g->img, x, sky_y, g->ceil_color);
		}
		y++;
	}
}
