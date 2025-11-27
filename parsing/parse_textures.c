/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:56:14 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 03:58:14 by carlos           ###   ########.fr       */
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

	f = open(path, 0);
	if (!f)
		return (set_error(ERR_TEXTURE_OPEN, path));
	close(f);
	return (0);
}

int	check_texture_path(const char *path)
{
	if (!path || !*path)
		return (set_error(ERR_TEXTURE_OPEN, "emptylspath"));
	if (open_test(path) != 0)
		return (-1);
	return (0);
}
