/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:56:14 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/23 00:38:54 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include "include/error.h"
#include "include/cub3d.h"

static int	open_test(const char *path, t_game *game)
{
	FILE	*f;

	f = fopen(path, "rb");
	if (!f)
		return (set_error(ERR_TEXTURE_OPEN, path, game));
	fclose(f);
	return (0);
}

static int	check_stat(const char *path, t_game *game)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (set_error(ERR_TEXTURE_OPEN, path, game));
#ifdef S_ISREG
	if (!S_ISREG(st.st_mode))
		return (set_error(ERR_TEXTURE_OPEN, path, game));
#endif
	return (0);
}

int	check_texture_path(const char *path, t_game *game)
{
	if (!path || !*path)
		return (set_error(ERR_TEXTURE_OPEN, "empty path", game));
	if (check_stat(path, game) != 0)
		return (-1);
	if (open_test(path, game) != 0)
		return (-1);
	return (0);
}
