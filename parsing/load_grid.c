/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 04:20:56 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 05:07:22 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/cub3d.h"
#include "../include/error.h"

void	place_player_more(t_game *game, char c)
{
	if (c == 'W')
	{
		game->p.dir_x = 0;
		game->p.dir_y = -1;
		game->p.plane_x = -0.66;
		game->p.plane_y = 0;
	}
	else if (c == 'E')
	{
		game->p.dir_x = 0;
		game->p.dir_y = 1;
		game->p.plane_x = 0.66;
		game->p.plane_y = 0;
	}
}

void	place_player_from_char(t_game *game, char c, int x, int y)
{
	game->p.pos_x = (double)x + 0.5;
	game->p.pos_y = (double)y + 0.5;
	if (c == 'N')
	{
		game->p.dir_x = -1;
		game->p.dir_y = 0;
		game->p.plane_x = 0;
		game->p.plane_y = 0.66;
	}
	else if (c == 'S')
	{
		game->p.dir_x = 1;
		game->p.dir_y = 0;
		game->p.plane_x = 0;
		game->p.plane_y = -0.66;
	}
	place_player_more(game, c);
}

void	check_grid(t_game *game, char c, int x, int y)
{
	if (c == '1')
		game->map[y][x] = 1;
	else if (c == '0')
		game->map[y][x] = 0;
	else if (c == ' ')
		game->map[y][x] = 1;
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->map[y][x] = 0;
		place_player_from_char(game, c, x, y);
	}
	else
		game->map[y][x] = 1;
}

int	load_map_into_grid(t_game *game)
{
	int		y;
	int		x;
	int		len;
	char	c;

	y = 0;
	while (y < game->m_h)
	{
		x = 0;
		while (x < game->m_w)
		{
			len = (int)ft_strlen(game->map_lines[y]);
			if (x < len)
				c = game->map_lines[y][x];
			else
				c = ' ';
			check_grid(game, c, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
