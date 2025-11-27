/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:58:42 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 04:35:08 by carlos           ###   ########.fr       */
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

void	free_lines(char **lines, int n)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < n)
	{
		free(lines[i]);
		lines[i] = NULL;
		i++;
	}
	free(lines);
}

void	clear_tex_paths(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->wall_tex[i])
		{
			free(game->wall_tex[i]);
			game->wall_tex[i] = NULL;
		}
		i++;
	}
}

int	has_cub_ext(const char *name)
{
	size_t	n;

	if (!name)
		return (0);
	n = ft_strlen(name);
	if (n < 4)
		return (0);
	return (ft_strncmp(name + n - 4, ".cub", 4) == 0);
}

void	free_map_lines(char **map, int h)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < h)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	set_map_all_ones(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->m_h)
	{
		x = 0;
		while (x < game->m_w)
		{
			game->map[y][x] = 1;
			x++;
		}
		y++;
	}
}
