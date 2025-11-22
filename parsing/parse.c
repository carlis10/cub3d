/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:58:42 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 20:12:07 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/cub3d.h"
#include "include/error.h"

int parse_identifier_line(char *line, t_game *game, int *have_tex,
						  int *have_floor, int *have_ceil);
int extract_map_block(char **file_lines, int nlines, int start_index,
					  char ***out_lines, int *out_h, int *out_w,
					  t_game *game);
int validate_map_block(char **map_lines, int map_h, int map_w, t_game *game);

static void	free_lines(char **lines, int n)
{
	int i;

	if (!lines)
		return ;
	for (i = 0; i < n; ++i)
	{
		free(lines[i]);
		lines[i] = NULL;
	}
	free(lines);
}

static void	clear_tex_paths(t_game *game)
{
	int i;

	if (!game)
		return ;
	for (i = 0; i < 4; ++i)
	{
		if (game->tex_path[i])
		{
			free(game->tex_path[i]);
			game->tex_path[i] = NULL;
		}
	}
}

static int	read_all_lines(const char *filename, char ***out_lines,
						   int *out_count, t_game *game)
{
	FILE	*f;
	char	*line;
	size_t	len;
	ssize_t	nread;
	char	**arr;
	int		count;

	f = fopen(filename, "r");
	if (!f)
		return (set_error(ERR_OPEN_FILE, filename, game));
	line = NULL;
	len = 0;
	arr = NULL;
	count = 0;
	while ((nread = getline(&line, &len, f)) != -1)
	{
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		char *dup = strdup(line);
		if (!dup)
		{
			free(line);
			fclose(f);
			free_lines(arr, count);
			return (set_error(ERR_MALLOC, "reading file", game));
		}
		char **tmp = realloc(arr, (count + 1) * sizeof(char *));
		if (!tmp)
		{
			free(dup);
			free(line);
			fclose(f);
			free_lines(arr, count);
			return (set_error(ERR_MALLOC, "reading file", game));
		}
		arr = tmp;
		arr[count++] = dup;
	}
	free(line);
	fclose(f);
	if (count == 0)
	{
		free(arr);
		return (set_error(ERR_READ_FILE, "file is empty", game));
	}
	*out_lines = arr;
	*out_count = count;
	return (0);
}

static int	has_cub_ext(const char *name)
{
	size_t n;

	if (!name)
		return (0);
	n = strlen(name);
	if (n < 4)
		return (0);
	return (strcmp(name + n - 4, ".cub") == 0);
}

int	parse_file(const char *filename, t_game *game)
{
	char	**lines;
	int		nlines;
	int		res;
	int		have_tex[4] = {0, 0, 0, 0};
	int		have_floor = 0;
	int		have_ceil = 0;
	int		i;

	if (!has_cub_ext(filename))
		return (set_error(ERR_BAD_EXTENSION, filename, game));
	lines = NULL;
	nlines = 0;
	res = read_all_lines(filename, &lines, &nlines, game);
	if (res != 0)
		return (-1);

	
	i = 0;
	while (i < nlines)
	{
		int r = parse_identifier_line(lines[i], game, have_tex, &have_floor,
									  &have_ceil);
		if (r == 0)
		{
			++i;
			continue ;
		}
		if (r == -1)
		{
			clear_tex_paths(game);
			free_lines(lines, nlines);
			return (-1);
		}
		break ;
	}
	if (!have_tex[0] || !have_tex[1] || !have_tex[2] || !have_tex[3]
		|| !have_floor || !have_ceil)
	{
		clear_tex_paths(game);
		free_lines(lines, nlines);
		return (set_error(ERR_MISSING_ID, "one or more identifiers missing", game));
	}
	{
		char **map_lines = NULL;
		int map_h = 0;
		int map_w = 0;

		if (extract_map_block(lines, nlines, i, &map_lines, &map_h, &map_w,
							  game) != 0)
		{
			clear_tex_paths(game);
			free_lines(lines, nlines);
			return (-1);
		}
		if (map_h > MAP_H || map_w > MAP_W)
		{
			for (int r = 0; r < map_h; ++r)
				free(map_lines[r]);
			free(map_lines);
			clear_tex_paths(game);
			free_lines(lines, nlines);
			return (set_error(ERR_MAP_INVALID,
				"map dimensions exceed supported MAP_W/MAP_H", game));
		}
		if (validate_map_block(map_lines, map_h, map_w, game) != 0)
		{
			for (int r = 0; r < map_h; ++r)
				free(map_lines[r]);
			free(map_lines);
			clear_tex_paths(game);
			free_lines(lines, nlines);
			return (-1);
		}
		for (int y = 0; y < MAP_H; ++y)
			for (int x = 0; x < MAP_W; ++x)
				game->map[y][x] = 1;

		for (int y = 0; y < map_h; ++y)
		{
			for (int x = 0; x < map_w; ++x)
			{
				char c = (x < (int)strlen(map_lines[y])) ? map_lines[y][x] : ' ';
				if (c == '1')
					game->map[y][x] = 1;
				else if (c == '0')
					game->map[y][x] = 0;
				else if (c == ' ')
					game->map[y][x] = 1;
				else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				{
					game->map[y][x] = 0;
					game->p.posX = x + 0.5;
					game->p.posY = y + 0.5;
					if (c == 'N')
					{
						game->p.dirX = -1;
						game->p.dirY = 0;
						game->p.planeX = 0;
						game->p.planeY = 0.66;
					}
					if (c == 'S')
					{
						game->p.dirX = 1;
						game->p.dirY = 0;
						game->p.planeX = 0;
						game->p.planeY = -0.66;
					}
					if (c == 'W')
					{
						game->p.dirX = 0;
						game->p.dirY = -1;
						game->p.planeX = -0.66;
						game->p.planeY = 0;
					}
					if (c == 'E')
					{
						game->p.dirX = 0;
						game->p.dirY = 1;
						game->p.planeX = 0.66;
						game->p.planeY = 0;
					}
				}
				else
					game->map[y][x] = 1;
			}
		}

		for (int r = 0; r < map_h; ++r)
			free(map_lines[r]);
		free(map_lines);
	}
	free_lines(lines, nlines);
	return (0);
}