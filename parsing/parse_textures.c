/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:56:14 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/23 16:07:11 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include "../include/error.h"
#include "../include/cub3d.h"

static int	open_test(const char *path)
{
	FILE	*f;

	f = fopen(path, "rb");
	if (!f)
		return (set_error(ERR_TEXTURE_OPEN, path));
	fclose(f);
	return (0);
}

static int	check_stat(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (set_error(ERR_TEXTURE_OPEN, path));
#ifdef S_ISREG
	if (!S_ISREG(st.st_mode))
		return (set_error(ERR_TEXTURE_OPEN, path));
#endif
	return (0);
}

int	check_texture_path(const char *path)
{
	if (!path || !*path)
		return (set_error(ERR_TEXTURE_OPEN, "emptylspath"));
	if (check_stat(path) != 0)
		return (-1);
	if (open_test(path) != 0)
		return (-1);
	return (0);
}
