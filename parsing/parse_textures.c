/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:56:14 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/26 20:23:16 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/error.h"
#include "../include/cub3d.h"

static int	open_test(const char *path)
{
	int	f;

	f = open(path, O_RDONLY);
	if (f < 0)
		return (set_error(ERR_TEXTURE_OPEN, path));
	close(f);
	return (0);
}

int	check_texture_path(const char *path)
{
	if (!path || !*path)
		return (set_error(ERR_TEXTURE_OPEN, "empty path"));
	if (open_test(path) != 0)
		return (-1);
	return (0);
}
