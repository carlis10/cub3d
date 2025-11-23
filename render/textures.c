/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:28:23 by carlos            #+#    #+#             */
/*   Updated: 2025/11/23 15:34:34 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
	int		idx;
	uint8_t	*px;

	if (!tex)
		return (0xFFFFFFFF);
	x = (x % tex->width + tex->width) % tex->width;
	y = (y % tex->height + tex->height) % tex->height;
	idx = (y * tex->width + x) * 4;
	px = &tex->pixels[idx];
	return ((px[0] << 24) | (px[1] << 16) | (px[2] << 8) | px[3]);
}

void	check_texture(mlx_texture_t *tex)
{
	if (!tex)
	{
		fprintf(stderr, " Error: no se pudo cargar la textura\n");
		exit(EXIT_FAILURE);
	}
}

void	draw_background(t_game *g)
{
	uint32_t	color;
	int			y;
	int			x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = 0x87CEEBFF;
		else
			color = 0x222222FF;
		while (x < WIDTH)
		{
			mlx_put_pixel(g->img, x, y, color);
			x++;
		}
		y++;
	}
}

mlx_texture_t	*w_t(t_game *g, int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x > 0)
			return (g->wall_tex[0]);
		else
			return (g->wall_tex[1]);
	}
	else
	{
		if (ray_dir_y > 0)
			return (g->wall_tex[2]);
		else
			return (g->wall_tex[3]);
	}
}
