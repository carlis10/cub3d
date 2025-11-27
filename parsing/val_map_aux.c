/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 23:30:37 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 02:37:23 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <ctype.h>
#include "../include/error.h"
#include "../include/cub3d.h"

char	get_char_map(int y, int x, char **map_lines)
{
	if (x < (int)strlen(map_lines[y]))
		return (map_lines[y][x]);
	else
		return (' ');
}

int	p_count(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_limits_map(int ny, int nx, t_game *g, char **map_lines)
{
	char	nc;

	if (ny < 0 || ny >= g->m_h || nx < 0 || nx >= g->m_w)
		return (set_error(ERR_MAP_NOT_CLOSED, "map has open edge"));
	if ((nx < (int)strlen(map_lines[ny])))
		nc = map_lines[ny][nx];
	else
		nc = ' ';
	if (nc == ' ')
		return (set_error(ERR_MAP_NOT_CLOSED, "space adjacent to floor"));
	return (0);
}

int	allowed_char(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (0);
	if (c == 'N')
		return (0);
	if (c == 'S')
		return (0);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (0);
	if (c == ' ')
		return (0);
	return (1);
}

int	count_player(t_game *g, int y, char **map_lines)
{
	int		x;
	char	c;
	int		player_count;

	x = 0;
	player_count = 0;
	while (x < g->m_w)
	{
		c = get_char_map(y, x, map_lines);
		if (allowed_char(c) != 0)
			return (set_error(ERR_INVALID_CHAR, "invalid character"));
		player_count += p_count(c);
		if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			if (!validate_edge_map(g, y, x, map_lines))
				return (-1);
		}
		x++;
	}
	return (player_count);
}
