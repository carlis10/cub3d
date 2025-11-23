/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:22:00 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/23 15:43:36 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

static const char *g_err_strings[] = {
	"Success",
	"Usage: ./cub3d <map.cub>",
	"Bad file extension (expected .cub)",
	"Could not open file",
	"Could not read file",
	"Duplicate identifier",
	"Missing identifier",
	"Texture file cannot be opened",
	"Texture failed to load",
	"Bad color format",
	"Color value out of range",
	"Invalid map",
	"Map is not closed/surrounded by walls",
	"Invalid character in map",
	"Invalid number of player starting positions",
	"Out of memory",
	"Failed to initialize graphics (MLX)",
	"Internal error"
};

int	set_error(t_error_code code, const char *detail)
{
	if (code <= ERR_NONE || code > ERR_INTERNAL)
		code = ERR_INTERNAL;
	(void)detail;
	return (-1);
}

void	print_error(t_error_code code, const char *detail)
{
	if (code <= ERR_NONE || code > ERR_INTERNAL)
		code = ERR_INTERNAL;
	fprintf(stderr, "Error\n%s", g_err_strings[code]);
	if (detail && detail[0] != '\0')
		fprintf(stderr, ": %s", detail);
	fprintf(stderr, "\n");
}

void	error_exit(t_error_code code, const char *detail)
{
	print_error(code, detail);
}