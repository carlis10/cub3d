/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:01 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/25 14:29:17 by carlos           ###   ########.fr       */
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

int alloc_map(t_game *game, int map_h, int map_w)
{
    game->m_h = map_h;
    game->m_w = map_w;

    game->map = malloc(sizeof(int *) * map_h);
    if (!game->map)
        return -1;

    for (int y = 0; y < map_h; y++)
    {
        game->map[y] = malloc(sizeof(int) * map_w);
        if (!game->map[y])
            return -1;
        for (int x = 0; x < map_w; x++)
            game->map[y][x] = 1; // inicializa seguro
    }
    return 0;
}

int	my_isspace(char c)
{
    return (c == ' '  || c == '\t' ||
            c == '\n' || c == '\r' ||
            c == '\v' || c == '\f');
}



