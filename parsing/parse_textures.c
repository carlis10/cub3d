/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:56:14 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 20:12:11 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include "include/error.h"
#include "include/cub3d.h"

int check_texture_path(const char *path, t_game *game)
{
	struct stat st;
	if (!path || !*path)
		return set_error(ERR_TEXTURE_OPEN, "empty path", game);
	if (stat(path, &st) != 0)
		return set_error(ERR_TEXTURE_OPEN, path, game);
#ifdef S_ISREG
	if (!S_ISREG(st.st_mode))
		return set_error(ERR_TEXTURE_OPEN, path, game);
#endif
	{
		FILE *f = fopen(path, "rb");
		if (!f) return set_error(ERR_TEXTURE_OPEN, path, game);
		fclose(f);
	}
	return 0;
}