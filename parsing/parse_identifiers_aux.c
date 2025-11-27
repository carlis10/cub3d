/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 00:05:17 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 03:58:43 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "../include/cub3d.h"
#include "../include/error.h"

void	init_tex_color(t_game *game)
{
	game->have_ceil = 0;
	game->have_floor = 0;
	game->have_tex[0] = 0;
	game->have_tex[1] = 0;
	game->have_tex[2] = 0;
	game->have_tex[3] = 0;
}

int	parse_identifier_line(char *line, t_game *game)
{
	const char	*t;

	t = skip_spaces_c(line);
	if (is_texture_id(t))
		return (parse_tex(t, game));
	if (t[0] == 'F' && (t[1] == ' ' || t[1] == '\0'))
		return (parse_color(t, &game->have_floor, &game->floor_color));
	if (t[0] == 'C' && (t[1] == ' ' || t[1] == '\0'))
		return (parse_color(t, &game->have_ceil, &game->ceil_color));
	return (1);
}
