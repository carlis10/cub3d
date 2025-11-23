/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:01 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/23 16:08:46 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include "../include/error.h"
#include "../include/cub3d.h"

static int allowed_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int validate_map_block(char **map_lines, int map_h, int map_w)
{
	int y, x;
	int player_count = 0;

	for (y = 0; y < map_h; ++y)
	{
		for (x = 0; x < map_w; ++x)
		{
			char c = (x < (int)strlen(map_lines[y])) ? map_lines[y][x] : ' ';
			if (!allowed_char(c))
				return set_error(ERR_INVALID_CHAR, "map contains invalid character");
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0 || y == map_h - 1 || x == 0 || x == map_w - 1)
					return set_error(ERR_MAP_NOT_CLOSED, "map touches boundary");
				
				for (int dy = -1; dy <= 1; ++dy)
				{
					for (int dx = -1; dx <= 1; ++dx)
					{
						int ny = y + dy;
						int nx = x + dx;
						if (ny < 0 || ny >= map_h || nx < 0 || nx >= map_w)
							return set_error(ERR_MAP_NOT_CLOSED, "map has open edge");
						char nc = (nx < (int)strlen(map_lines[ny])) ? map_lines[ny][nx] : ' ';
						if (nc == ' ')
							return set_error(ERR_MAP_NOT_CLOSED, "map has space adjacent to floor");
					}
				}
			}
		}
	}
	if (player_count != 1)
		return set_error(ERR_PLAYER_COUNT, "exactly one player required");
	return 0;
}