/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 04:10:16 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 05:10:53 by carlos           ###   ########.fr       */
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

int	parse_f(const char *filename, t_game *game, char ***lines, int *nlines)
{
	int		res;
	int		ln;
	char	**lin;

	if (!has_cub_ext(filename))
		return (set_error(ERR_BAD_EXTENSION, filename));
	res = read_all_l(filename, &lin, &ln);
	if (res != 0)
		return (-1);
	init_tex_color(game);
	*nlines = ln;
	*lines = lin;
	return (0);
}

int	parse_second(int nlines, char **lines, t_game *game, int *i)
{
	int	res;

	while (*i < nlines)
	{
		res = parse_identifier_line(lines[*i], game);
		if (res == 0)
		{
			(*i)++;
			continue ;
		}
		if (res == -1)
		{
			clear_tex_paths(game);
			free_lines(lines, nlines);
			return (-1);
		}
		if (game->have_tex[0] && game->have_tex[1]
			&& game->have_tex[2] && game->have_tex[3]
			&& game->have_floor && game->have_ceil)
			break ;
		(*i)++;
	}
	return (0);
}

int	check_identifiers(t_game *game, char **lines, int nlines)
{
	if (!game->have_tex[0] || !game->have_tex[1]
		|| !game->have_tex[2] || !game->have_tex[3]
		|| !game->have_floor || !game->have_ceil)
	{
		clear_tex_paths(game);
		free_lines(lines, nlines);
		return (set_error(ERR_MISSING_ID, "one or more identifiers missing"));
	}
	return (0);
}

int	parse_file(const char *filename, t_game *game)
{
	char	**lines;
	int		nlines;
	int		i;

	i = 0;
	if (parse_f(filename, game, &lines, &nlines) != 0)
		return (-1);
	if (parse_second(nlines, lines, game, &i) != 0)
		return (-1);
	if (check_identifiers(game, lines, nlines) != 0)
		return (-1);
	game->map_lines = NULL;
	if (extract_m_b(lines, nlines, i, game) != 0)
		return (cleanup_and_err(lines, nlines, game));
	if (validate_map_block(game->map_lines, game) != 0)
		return (cleanup_and_err(lines, nlines, game));
	if (alloc_map(game, game->m_h, game->m_w) != 0)
		return (cleanup_and_err(lines, nlines, game));
	set_map_all_ones(game);
	if (load_map_into_grid(game) != 0)
		return (cleanup_and_err(lines, nlines, game));
	free_map_lines(game->map_lines, game->m_h);
	free_lines(lines, nlines);
	return (0);
}

int	cleanup_and_err(char **lines, int nlines, t_game *game)
{
	if (game->map_lines)
		free_map_lines(game->map_lines, game->m_h);
	clear_tex_paths(game);
	free_lines(lines, nlines);
	return (-1);
}
