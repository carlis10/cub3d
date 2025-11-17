/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:28:23 by carlos            #+#    #+#             */
/*   Updated: 2025/11/17 16:17:10 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	if (!tex)
		return (0xFFFFFFFF);
	x = (x % tex->width + tex->width) % tex->width;
	y = (y % tex->height + tex->height) % tex->height;
	int idx = (y * tex->width + x) * 4;
	uint8_t *px = &tex->pixels[idx];
	return ((px[0] << 24) | (px[1] << 16) | (px[2] << 8) | px[3]);
}

void check_texture(mlx_texture_t *tex, const char *name)
{
	if (!tex)
	{
		fprintf(stderr, "❌ Error: no se pudo cargar %s\n", name);
		exit(EXIT_FAILURE);
	}
	printf("✅ Cargada: %s (%dx%d)\n", name, tex->width, tex->height);
}

void draw_background(t_game *g)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		uint32_t color = (y < HEIGHT / 2) ? 0x87CEEBFF : 0x222222FF;
		for (int x = 0; x < WIDTH; x++)
			mlx_put_pixel(g->img, x, y, color);
	}
}

mlx_texture_t *choose_wall_texture(t_game *g, int side, double rayDirX, double rayDirY)
{
    if (side == 0)
		if (rayDirX > 0) 
           return (g->wallTex[0]);
		else
			return (g->wallTex[1]);
    else
		if (rayDirY > 0) 
           return (g->wallTex[2]);
		else
			return (g->wallTex[3]);
}

