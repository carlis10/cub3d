/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:33:28 by carlos            #+#    #+#             */
/*   Updated: 2025/11/17 16:17:03 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void cast_ray(t_game *g, int x)
{
	double cameraX = 2 * x / (double)WIDTH - 1;
	double rayDirX = g->p.dirX + g->p.planeX * cameraX;
	double rayDirY = g->p.dirY + g->p.planeY * cameraX;
	int mapX = (int)g->p.posX;
	int mapY = (int)g->p.posY;
	double sideDistX, sideDistY;
	double deltaX = (rayDirX == 0.0) ? 1e30 : fabs(1.0 / rayDirX);
	double deltaY = (rayDirY == 0.0) ? 1e30 : fabs(1.0 / rayDirY);
	int stepX, stepY, hit = 0, side;

	if (rayDirX < 0) { stepX = -1; sideDistX = (g->p.posX - mapX) * deltaX; }
	else { stepX = 1; sideDistX = (mapX + 1.0 - g->p.posX) * deltaX; }
	if (rayDirY < 0) { stepY = -1; sideDistY = (g->p.posY - mapY) * deltaY; }
	else { stepY = 1; sideDistY = (mapY + 1.0 - g->p.posY) * deltaY; }

	/* DDA con protección de límites */
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaY;
			mapY += stepY;
			side = 1;
		}
		/* proteger acceso al mapa */
		if (mapX < 0 || mapX >= MAP_W || mapY < 0 || mapY >= MAP_H)
		{
			/* rayo salió del mapa: no dibujamos pared */
			hit = 0;
			break;
		}
		if (g->map[mapY][mapX] > 0)
			hit = 1;
	}

	/* Si no hubo impacto válido, salimos sin dibujar muro (pero podemos hacer floor) */
	if (!hit)
		return;

	/* distancia perpendicular (proteger divisiones) */
	double dist;
	if (side == 0)
		dist = (rayDirX == 0.0) ? 1e-6
			: (mapX - g->p.posX + (1 - stepX) / 2.0) / rayDirX;
	else
		dist = (rayDirY == 0.0) ? 1e-6
			: (mapY - g->p.posY + (1 - stepY) / 2.0) / rayDirY;
	if (!isfinite(dist) || dist <= 0.0)
		dist = 1e-6;

	double wallX = (side == 0) ? g->p.posY + dist * rayDirY
							  : g->p.posX + dist * rayDirX;
	wallX -= floor(wallX);

	draw_wall(g, x, dist, side, wallX, rayDirX, rayDirY);
	/* calculamos drawEnd como lo hacía antes pero con protección */
	int lineHeight = (int)(HEIGHT / dist);
	int drawEnd = lineHeight / 2 + HEIGHT / 2;
	if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
	draw_floor_sky(g, x, drawEnd, dist);
}

void draw_scene(t_game *g)
{
	draw_background(g);
	for (int x = 0; x < WIDTH; x++)
		cast_ray(g, x);
}
