/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:48 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/23 00:38:54 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/error.h"
#include "include/cub3d.h"

static int	is_blank_line(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (!isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

static int	free_map_lines(char **map, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (-1);
}

static int	append_map_line(char ***map, int *h, const char *src, t_game *game)
{
	char	**tmp;
	char	*dup;

	dup = strdup(src);
	if (!dup)
		return (set_error(ERR_MALLOC, "map duplicate", game));
	tmp = realloc(*map, sizeof(char *) * (*h + 1));
	if (!tmp)
	{
		free(dup);
		return (set_error(ERR_MALLOC, "map lines", game));
	}
	*map = tmp;
	(*map)[*h] = dup;
	(*h)++;
	return (0);
}

static int	process_map_lines(char **file_lines, int nlines, int start,
		char ***map, int *map_h, int *map_w, t_game *game)
{
	int	i;
	int	len;

	i = start;
	while (i < nlines)
	{
		if (is_blank_line(file_lines[i]))
			return (set_error(ERR_MAP_INVALID, "empty line inside map", game));
		len = (int)strlen(file_lines[i]);
		if (len > *map_w)
			*map_w = len;
		if (append_map_line(map, map_h, file_lines[i], game) != 0)
			return (free_map_lines(*map, *map_h));
		i++;
	}
	return (0);
}

int	extract_map_block(char **file_lines, int nlines, int start_index,
		char ***out_lines, int *out_h, int *out_w, t_game *game)
{
	int		i;
	char	**map_lines;
	int		map_h;
	int		map_w;

	i = start_index;
	map_lines = NULL;
	map_h = 0;
	map_w = 0;
	while (i < nlines && is_blank_line(file_lines[i]))
		i++;
	if (i >= nlines)
		return (set_error(ERR_MAP_INVALID,
				"map missing after identifiers", game));
	if (process_map_lines(file_lines, nlines, i,
			&map_lines, &map_h, &map_w, game) != 0)
		return (-1);
	if (map_h == 0)
	{
		free(map_lines);
		return (set_error(ERR_MAP_INVALID, "map missing", game));
	}
	*out_lines = map_lines;
	*out_h = map_h;
	*out_w = map_w;
	return (0);
}