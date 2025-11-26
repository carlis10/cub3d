/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:54:07 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/26 20:23:16 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../include/cub3d.h"
#include "../include/error.h"


static const char	*skip_spaces_c(const char *s)
{
	while (*s && my_isspace((unsigned char)*s))
		s++;
	return (s);
}

static int	load_texture_into_game(t_game *game, const char *path, int idx)
{
	mlx_texture_t	*text;

	text = mlx_load_png(path);
	check_texture(text);
	game->wall_tex[idx] = text;
	return (0);
}

static int	set_texture_path(t_game *game, const char *path, int idx)
{
	if (check_texture_path(path) != 0)
		return (-1);
	return (load_texture_into_game(game, path, idx));
}

static int	check_dup_texture(int *have_tex, const char *t)
{
	if (have_tex[0] && t[0] == 'N' && t[1] == 'O')
		return (set_error(ERR_DUP_ID, "NO"));
	if (have_tex[1] && t[0] == 'S' && t[1] == 'O')
		return (set_error(ERR_DUP_ID, "SO"));
	if (have_tex[2] && t[0] == 'W' && t[1] == 'E')
		return (set_error(ERR_DUP_ID, "WE"));
	if (have_tex[3] && t[0] == 'E' && t[1] == 'A')
		return (set_error(ERR_DUP_ID, "EA"));
	return (0);
}

static int	assign_texture(t_game *game,
		const char *path, int *have_tex, const char *t)
{
	if (t[0] == 'N')
	{
		have_tex[0] = 1;
		return (set_texture_path(game, path, 0));
	}
	if (t[0] == 'S')
	{
		have_tex[1] = 1;
		return (set_texture_path(game, path, 1));
	}
	if (t[0] == 'W')
	{
		have_tex[2] = 1;
		return (set_texture_path(game, path, 2));
	}
	have_tex[3] = 1;
	return (set_texture_path(game, path, 3));
}

static int	parse_tex(const char *t, t_game *game, int *have_tex)
{
	const char	*path;

	if (check_dup_texture(have_tex, t) != 0)
		return (-1);
	path = skip_spaces_c(t + 2);
	if (*path == '\0')
		return (set_error(ERR_TEXTURE_OPEN, "empty path"));
	return (assign_texture(game, path, have_tex, t));
}

static int	is_texture_id(const char *t)
{
	if ((t[0] == 'N' && t[1] == 'O') || (t[0] == 'S' && t[1] == 'O'))
		return (1);
	if ((t[0] == 'W' && t[1] == 'E') || (t[0] == 'E' && t[1] == 'A'))
		return (1);
	return (0);
}

static int	check_color_dup(const char *t, int *have_color)
{
	if (*have_color)
	{
		if (t[0] == 'F')
			return (set_error(ERR_DUP_ID, "F"));
		return (set_error(ERR_DUP_ID, "C"));
	}
	return (0);
}

static int	parse_color(const char *t, int *have_color, int *dst)
{
	const char	*args;

	if (check_color_dup(t, have_color) != 0)
		return (-1);
	args = skip_spaces_c(t + 1);
	if (parse_rgb_line(args, dst) != 0)
		return (-1);
	*have_color = 1;
	return (0);
}

int	parse_identifier_line(char *line, t_game *game,
		int *have_tex, int *have_floor, int *have_ceil)
{
	const char	*t;

	t = skip_spaces_c(line);
	if (is_texture_id(t))
		return (parse_tex(t, game, have_tex));
	if (t[0] == 'F' && (t[1] == ' ' || t[1] == '\0'))
		return (parse_color(t, have_floor, &game->floor_color));
	if (t[0] == 'C' && (t[1] == ' ' || t[1] == '\0'))
		return (parse_color(t, have_ceil, &game->ceil_color));
	return (1);
}
