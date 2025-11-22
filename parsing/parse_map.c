/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:48 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 20:12:12 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/error.h"
#include "include/cub3d.h"

static int is_blank_line(const char *s)
{
	if (!s) return 1;
	while (*s)
	{
		if (!isspace((unsigned char)*s))
			return 0;
		++s;
	}
	return 1;
}

int extract_map_block(char **file_lines, int nlines, int start_index,
	char ***out_lines, int *out_h, int *out_w, t_game *game)
{
	int i = start_index;
	int map_h = 0;
	int map_w = 0;
	char **map_lines = NULL;

	while (i < nlines && is_blank_line(file_lines[i]))
		++i;
	if (i >= nlines)
		return set_error(ERR_MAP_INVALID, "map missing after identifiers", game);

	
	for (; i < nlines; ++i)
	{
		if (is_blank_line(file_lines[i]))
			return set_error(ERR_MAP_INVALID, "empty line inside map", game);
		int thisw = (int)strlen(file_lines[i]);
		if (thisw > map_w) map_w = thisw;
		char *dup = strdup(file_lines[i]);
		if (!dup)
		{
			for (int k = 0; k < map_h; ++k) free(map_lines[k]);
			free(map_lines);
			return set_error(ERR_MALLOC, "map duplicate", game);
		}
		char **tmp = realloc(map_lines, sizeof(char *) * (map_h + 1));
		if (!tmp)
		{
			free(dup);
			for (int k = 0; k < map_h; ++k) free(map_lines[k]);
			free(map_lines);
			return set_error(ERR_MALLOC, "map lines", game);
		}
		map_lines = tmp;
		map_lines[map_h++] = dup;
	}
	if (map_h == 0)
	{
		if (map_lines) free(map_lines);
		return set_error(ERR_MAP_INVALID, "map missing", game);
	}
	*out_lines = map_lines;
	*out_h = map_h;
	*out_w = map_w;
	return 0;
}