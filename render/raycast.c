/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:35:21 by carlos            #+#    #+#             */
/*   Updated: 2025/11/17 16:17:06 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_wall(t_game *g, int x, double perpWallDist, int side,
	double wallX, double rayDirX, double rayDirY)
{
	if (perpWallDist <= 0.0 || !isfinite(perpWallDist))
		return;
	int lineHeight = (int)(HEIGHT / perpWallDist);
	int drawStart = -lineHeight / 2 + HEIGHT / 2;
	if (drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + HEIGHT / 2;
	if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

	int texX = (int)(wallX * TEX_W);
	if (side == 0 && rayDirX > 0) texX = TEX_W - texX - 1;
	if (side == 1 && rayDirY < 0) texX = TEX_W - texX - 1;

	/* textura segura */
	mlx_texture_t *tex = choose_wall_texture(g, side, rayDirX, rayDirY);
	int w = (tex && tex->width) ? tex->width : TEX_W;
	int h = (tex && tex->height) ? tex->height : TEX_H;

	for (int y = drawStart; y <= drawEnd; y++)
	{
		int d = y * 256 - HEIGHT * 128 + lineHeight * 128;
		int texY = ((d * h) / lineHeight) / 256;
		/* corrección segura de índices */
		int tx = ((texX % w) + w) % w;
		int ty = ((texY % h) + h) % h;
		uint32_t color = get_tex_pixel(tex, tx, ty);
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			mlx_put_pixel(g->img, x, y, color);
	}
}

void draw_floor_sky(t_game *g, int x, int drawEnd, double perpWallDist)
{
	if (perpWallDist <= 0.0 || !isfinite(perpWallDist))
		return;
	for (int y = drawEnd + 1; y < HEIGHT; y++)
	{
		double currentDist = HEIGHT / (2.0 * y - HEIGHT);
		/* proteger currentDist infinito/NaN */
		if (!isfinite(currentDist) || currentDist <= 0.0)
			continue;

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			mlx_put_pixel(g->img, x, y, 0);
			int sky_y = HEIGHT - y;
			if (sky_y >= 0 && sky_y < HEIGHT)
				mlx_put_pixel(g->img, x, sky_y, 0);
		}
	}
}
