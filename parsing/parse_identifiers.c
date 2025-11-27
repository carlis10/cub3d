/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:54:07 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 04:03:14 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../include/cub3d.h"
#include "../include/error.h"

const char	*skip_spaces_c(const char *s)
{
	while (*s && my_isspace((unsigned char)*s))
		s++;
	return (s);
}

int	set_texture_path(t_game *game, const char *path, int idx)
{
	mlx_texture_t	*text;

	if (check_texture_path(path) != 0)
		return (-1);
	text = mlx_load_png(path);
	check_texture(text);
	game->wall_tex[idx] = text;
	return (0);
}

int	parse_tex(const char *t, t_game *game)
{
	const char	*path;

	if (game->have_tex[0] && t[0] == 'N' && t[1] == 'O')
		return (set_error(ERR_DUP_ID, "NO"));
	if (game->have_tex[1] && t[0] == 'S' && t[1] == 'O')
		return (set_error(ERR_DUP_ID, "SO"));
	if (game->have_tex[2] && t[0] == 'W' && t[1] == 'E')
		return (set_error(ERR_DUP_ID, "WE"));
	if (game->have_tex[3] && t[0] == 'E' && t[1] == 'A')
		return (set_error(ERR_DUP_ID, "EA"));
	path = skip_spaces_c(t + 2);
	if (*path == '\0')
		return (set_error(ERR_TEXTURE_OPEN, "empty path"));
	if (t[0] == 'N')
		return (game->have_tex[0] = 1, set_texture_path(game, path, 0));
	if (t[0] == 'S')
		return (game->have_tex[1] = 1, set_texture_path(game, path, 1));
	if (t[0] == 'W')
		return (game->have_tex[2] = 1, set_texture_path(game, path, 2));
	return (game->have_tex[3] = 1, set_texture_path(game, path, 3));
}

int	is_texture_id(const char *t)
{
	if ((t[0] == 'N' && t[1] == 'O') || (t[0] == 'S' && t[1] == 'O'))
		return (1);
	if ((t[0] == 'W' && t[1] == 'E') || (t[0] == 'E' && t[1] == 'A'))
		return (1);
	return (0);
}

int	parse_color(const char *t, int *have_color, int *dst)
{
	const char	*args;

	if (*have_color)
	{
		if (t[0] == 'F')
			return (set_error(ERR_DUP_ID, "F"));
		else
			return (set_error(ERR_DUP_ID, "C"));
	}
	args = skip_spaces_c(t + 1);
	if (parse_rgb_line(args, dst) != 0)
		return (-1);
	*have_color = 1;
	return (0);
}
