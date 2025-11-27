/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:01 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 05:54:07 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include "../include/error.h"
#include "../include/cub3d.h"

int	validate_edge_map(t_game *g, int y, int x, char **map_lines)
{
	int	dy;
	int	dx;
	int	ny;
	int	nx;

	if (y == 0 || y == g->m_h - 1 || x == 0 || x == g->m_w - 1)
		return (set_error(ERR_MAP_NOT_CLOSED, "map not closed"));
	dy = 0;
	while (dy <= 1)
	{
		dx = 0;
		while (dx <= 1)
		{
			ny = y + dy;
			nx = x + dx;
			if (!check_limits_map(ny, nx, g, map_lines))
				return (-1);
			dx++;
		}
		dy++;
	}
	return (0);
}

int	validate_map_block(char **map_lines, t_game *g)
{
	int		y;
	int		player_count;
	int		plyr;

	y = 0;
	player_count = 0;
	plyr = 0;
	while (y < g->m_h)
	{
		player_count = count_player(g, y, map_lines);
		if (player_count == 1)
			plyr += player_count;
		if (player_count == -1)
			return (-1);
		y++;
	}
	if (plyr != 1)
		return (set_error(ERR_PLAYER_COUNT, "exactly one player required"));
	return (0);
}

int	alloc_map(t_game *game, int map_h, int map_w)
{
	int	y;
	int	x;

	game->m_h = map_h;
	game->m_w = map_w;
	game->map = malloc(sizeof(int *) * map_h);
	if (!game->map)
		return (set_error(ERR_MALLOC, "malloc map error"));
	y = 0;
	while (y < map_h)
	{
		x = 0;
		game->map[y] = malloc(sizeof(int) * map_w);
		if (!game->map[y])
			return (set_error(ERR_MALLOC, "malloc map error"));
		while (x < map_w)
		{
			game->map[y][x] = 1;
			x++;
		}
		y++;
	}
	return (0);
}

int	my_isspace(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}
