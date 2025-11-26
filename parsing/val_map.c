/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:01 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/26 20:23:16 by javierzarag      ###   ########.fr       */
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

static int	check_adjacent(char **map, int map_h, int map_w, int y, int x)
{
	int	dy;
	int	dx;
	int	ny;
	int	nx;
	int	len;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			ny = y + dy;
			nx = x + dx;
			if (ny < 0 || ny >= map_h || nx < 0 || nx >= map_w)
				return (set_error(ERR_MAP_NOT_CLOSED, "map has open edge"));
			len = (int)strlen(map[ny]);
			if (nx < len && map[ny][nx] == ' ')
				return (set_error(ERR_MAP_NOT_CLOSED,
						"map has space adjacent to floor"));
			dx++;
		}
		dy++;
	}
	return (0);
}

static int	check_cell(char **map, int map_h, int map_w, int y, int x)
{
	char	c;

	c = (x < (int)strlen(map[y])) ? map[y][x] : ' ';
	if (!allowed_char(c))
		return (set_error(ERR_INVALID_CHAR,
				"map contains invalid character"));
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (y == 0 || y == map_h - 1 || x == 0 || x == map_w - 1)
			return (set_error(ERR_MAP_NOT_CLOSED, "map touches boundary"));
		return (check_adjacent(map, map_h, map_w, y, x));
	}
	return (0);
}

static int	count_players_in_row(char *line, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			count++;
		i++;
	}
	return (count);
}

int	validate_map_block(char **map, int map_h, int map_w)
{
	int	y;
	int	x;
	int	res;
	int	player_count;

	y = 0;
	player_count = 0;
	while (y < map_h)
	{
		x = 0;
		while (x < map_w)
		{
			res = check_cell(map, map_h, map_w, y, x);
			if (res != 0)
				return (res);
			if (x < (int)strlen(map[y]))
				player_count += count_players_in_row(map[y], x + 1)
					- count_players_in_row(map[y], x);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (set_error(ERR_PLAYER_COUNT, "exactly one player required"));
	return (0);
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
            game->map[y][x] = 1;
    }
    return 0;
}

int	my_isspace(char c)
{
    return (c == ' '  || c == '\t' ||
            c == '\n' || c == '\r' ||
            c == '\v' || c == '\f');
}



