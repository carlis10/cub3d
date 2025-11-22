/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:54:07 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 20:12:13 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/cub3d.h"
#include "include/error.h"


int parse_rgb_line(const char *args, int *out_color, t_game *game);
int check_texture_path(const char *path, t_game *game);


static const char *skip_spaces_c(const char *s)
{
	while (*s && isspace((unsigned char)*s))
		++s;
	return s;
}

int parse_identifier_line(char *line, t_game *game, int *have_tex, int *have_floor, int *have_ceil)
{
	const char *t = skip_spaces_c(line);

	if (strncmp(t, "NO", 2) == 0 && (t[2] == ' ' || t[2] == '\0'))
	{
		const char *path = skip_spaces_c(t + 2);
		if (*path == '\0') return set_error(ERR_TEXTURE_OPEN, "NO has empty path", game);
		if (have_tex[0]) return set_error(ERR_DUP_ID, "NO", game);
		if (check_texture_path(path, game) != 0) return -1;
		game->tex_path[0] = strdup(path);
		if (!game->tex_path[0]) return set_error(ERR_MALLOC, "NO path", game);
		have_tex[0] = 1;
		return 0;
	}
	if (strncmp(t, "SO", 2) == 0 && (t[2] == ' ' || t[2] == '\0'))
	{
		const char *path = skip_spaces_c(t + 2);
		if (*path == '\0') return set_error(ERR_TEXTURE_OPEN, "SO has empty path", game);
		if (have_tex[1]) return set_error(ERR_DUP_ID, "SO", game);
		if (check_texture_path(path, game) != 0) return -1;
		game->tex_path[1] = strdup(path);
		if (!game->tex_path[1]) return set_error(ERR_MALLOC, "SO path", game);
		have_tex[1] = 1;
		return 0;
	}
	if (strncmp(t, "WE", 2) == 0 && (t[2] == ' ' || t[2] == '\0'))
	{
		const char *path = skip_spaces_c(t + 2);
		if (*path == '\0') return set_error(ERR_TEXTURE_OPEN, "WE has empty path", game);
		if (have_tex[2]) return set_error(ERR_DUP_ID, "WE", game);
		if (check_texture_path(path, game) != 0) return -1;
		game->tex_path[2] = strdup(path);
		if (!game->tex_path[2]) return set_error(ERR_MALLOC, "WE path", game);
		have_tex[2] = 1;
		return 0;
	}
	if (strncmp(t, "EA", 2) == 0 && (t[2] == ' ' || t[2] == '\0'))
	{
		const char *path = skip_spaces_c(t + 2);
		if (*path == '\0') return set_error(ERR_TEXTURE_OPEN, "EA has empty path", game);
		if (have_tex[3]) return set_error(ERR_DUP_ID, "EA", game);
		if (check_texture_path(path, game) != 0) return -1;
		game->tex_path[3] = strdup(path);
		if (!game->tex_path[3]) return set_error(ERR_MALLOC, "EA path", game);
		have_tex[3] = 1;
		return 0;
	}
	if (t[0] == 'F' && (t[1] == ' ' || t[1] == '\0'))
	{
		const char *args = skip_spaces_c(t + 1);
		if (*have_floor) return set_error(ERR_DUP_ID, "F", game);
		if (parse_rgb_line(args, &game->floor_color, game) != 0) return -1;
		*have_floor = 1;
		return 0;
	}
	if (t[0] == 'C' && (t[1] == ' ' || t[1] == '\0'))
	{
		const char *args = skip_spaces_c(t + 1);
		if (*have_ceil) return set_error(ERR_DUP_ID, "C", game);
		if (parse_rgb_line(args, &game->ceil_color, game) != 0) return -1;
		*have_ceil = 1;
		return 0;
	}
	return 1; 
}