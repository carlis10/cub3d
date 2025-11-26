/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:58:42 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/26 20:23:16 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/cub3d.h"
#include "../include/error.h"

static void	free_lines(char **lines, int n)
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

static void	clear_textures(t_game *game)
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

static int	has_cub_ext(const char *name)
{
	size_t	len;

	if (!name)
		return (0);
	len = strlen(name);
	if (len < 4)
		return (0);
	return (strcmp(name + len - 4, ".cub") == 0);
}

static int	append_line(char ***arr, int *count, char *dup)
{
	char	**tmp;

	tmp = realloc(*arr, sizeof(char *) * (*count + 1));
	if (!tmp)
	{
		free(dup);
		return (-1);
	}
	*arr = tmp;
	(*arr)[*count] = dup;
	(*count)++;
	return (0);
}

static int	read_single_line(FILE *f, char ***arr, int *count)
{
	char	*line;
	size_t	len;
	int		nread;
	char	*dup;

	line = NULL;
	len = 0;
	nread = getline(&line, &len, f);
	if (nread == -1)
	{
		free(line);
		return (0);
	}
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
	dup = strdup(line);
	free(line);
	if (!dup)
		return (-1);
	if (append_line(arr, count, dup) != 0)
		return (-1);
	return (1);
}

static int	read_all_lines(const char *filename, char ***out_lines, int *out_count)
{
	FILE	*f;
	char	**arr;
	int		count;
	int		res;

	f = fopen(filename, "r");
	if (!f)
		return (set_error(ERR_OPEN_FILE, filename));
	arr = NULL;
	count = 0;
	while (1)
	{
		res = read_single_line(f, &arr, &count);
		if (res == 0)
			break ;
		if (res == -1)
		{
			free_lines(arr, count);
			fclose(f);
			return (set_error(ERR_MALLOC, "reading file"));
		}
	}
	fclose(f);
	if (count == 0)
		return (set_error(ERR_READ_FILE, "file is empty"));
	*out_lines = arr;
	*out_count = count;
	return (0);
}

static void	free_map_lines(char **map, int h)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < h)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

static void	set_map_all_ones(t_game *game)
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

static void	set_player_north(t_game *game)
{
	game->p.dir_x = -1;
	game->p.dir_y = 0;
	game->p.plane_x = 0;
	game->p.plane_y = 0.66;
}

static void	set_player_south(t_game *game)
{
	game->p.dir_x = 1;
	game->p.dir_y = 0;
	game->p.plane_x = 0;
	game->p.plane_y = -0.66;
}

static void	set_player_west(t_game *game)
{
	game->p.dir_x = 0;
	game->p.dir_y = -1;
	game->p.plane_x = -0.66;
	game->p.plane_y = 0;
}

static void	set_player_east(t_game *game)
{
	game->p.dir_x = 0;
	game->p.dir_y = 1;
	game->p.plane_x = 0.66;
	game->p.plane_y = 0;
}

static void	place_player(t_game *game, char c, int x, int y)
{
	game->p.pos_x = (double)x + 0.5;
	game->p.pos_y = (double)y + 0.5;
	if (c == 'N')
		set_player_north(game);
	else if (c == 'S')
		set_player_south(game);
	else if (c == 'W')
		set_player_west(game);
	else if (c == 'E')
		set_player_east(game);
}

static int	load_map_cell(t_game *game, char c, int x, int y)
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
		place_player(game, c, x, y);
	}
	else
		game->map[y][x] = 1;
	return (0);
}

static int	load_map_into_grid(char **map_lines, int map_h, int map_w,
		t_game *game)
{
	int	y;
	int	x;
	int	len;
	char	c;

	y = 0;
	while (y < map_h)
	{
		x = 0;
		while (x < map_w)
		{
			len = (int)strlen(map_lines[y]);
			c = (x < len) ? map_lines[y][x] : ' ';
			load_map_cell(game, c, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

static int	cleanup_and_err(char **lines, int nlines, char **map_lines,
		int map_h, t_game *game)
{
	if (map_lines)
		free_map_lines(map_lines, map_h);
	clear_textures(game);
	free_lines(lines, nlines);
	return (-1);
}

static int	parse_identifiers(char **lines, int nlines, t_game *game,
		int *have_tex, int *have_floor, int *have_ceil, int *index)
{
	int	res;
	int	i;

	i = 0;
	while (i < nlines)
	{
		res = parse_identifier_line(lines[i], game, have_tex,
				have_floor, have_ceil);
		if (res == 0)
		{
			i++;
			continue ;
		}
		if (res == -1)
			return (-1);
		if (have_tex[0] && have_tex[1] && have_tex[2] && have_tex[3]
			&& *have_floor && *have_ceil)
			break ;
		i++;
	}
	*index = i;
	if (!have_tex[0] || !have_tex[1] || !have_tex[2] || !have_tex[3]
		|| !*have_floor || !*have_ceil)
		return (-1);
	return (0);
}

int	parse_file(const char *filename, t_game *game)
{
	char	**lines;
	int		nlines;
	int		have_tex[4] = {0, 0, 0, 0};
	int		have_floor = 0;
	int		have_ceil = 0;
	int		i;
	char	**map_lines;
	int		map_h;
	int		map_w;
	int		res;

	if (!has_cub_ext(filename))
		return (set_error(ERR_BAD_EXTENSION, filename));
	lines = NULL;
	nlines = 0;
	res = read_all_lines(filename, &lines, &nlines);
	if (res != 0)
		return (-1);
	if (parse_identifiers(lines, nlines, game, have_tex, &have_floor,
			&have_ceil, &i) != 0)
		return (cleanup_and_err(lines, nlines, NULL, 0, game));
	map_lines = NULL;
	map_h = 0;
	map_w = 0;
	if (extract_map_block(lines, nlines, i, &map_lines, &map_h, &map_w) != 0)
		return (cleanup_and_err(lines, nlines, map_lines, map_h, game));
	if (validate_map_block(map_lines, map_h, map_w) != 0)
		return (cleanup_and_err(lines, nlines, map_lines, map_h, game));
	if (alloc_map(game, map_h, map_w) != 0)
		return (cleanup_and_err(lines, nlines, map_lines, map_h, game));
	set_map_all_ones(game);
	if (load_map_into_grid(map_lines, map_h, map_w, game) != 0)
		return (cleanup_and_err(lines, nlines, map_lines, map_h, game));
	free_map_lines(map_lines, map_h);
	free_lines(lines, nlines);
	return (0);
}
