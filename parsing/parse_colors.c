/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:55:17 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 20:12:14 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "include/error.h"
#include "include/cub3d.h"

int parse_rgb_line(const char *s, int *out_color, t_game *game)
{
	int vals[3];
	int idx = 0;
	const char *p = s;

	if (!s) return set_error(ERR_COLOR_FORMAT, "empty color", game);
	while (*p && isspace((unsigned char)*p)) ++p;

	for (idx = 0; idx < 3; ++idx)
	{
		if (!isdigit((unsigned char)*p))
			return set_error(ERR_COLOR_FORMAT, s, game);
		int v = 0;
		while (*p && isdigit((unsigned char)*p))
		{
			v = v * 10 + (*p - '0');
			++p;
			if (v > 255) return set_error(ERR_COLOR_VALUE, s, game);
		}
		vals[idx] = v;
		if (idx < 2)
		{
			if (*p != ',') return set_error(ERR_COLOR_FORMAT, s, game);
			++p;
			while (*p && isspace((unsigned char)*p)) ++p;
		}
	}
	while (*p)
	{
		if (!isspace((unsigned char)*p))
			return set_error(ERR_COLOR_FORMAT, s, game);
		++p;
	}
	*out_color = (vals[0] << 24) | (vals[1] << 16) | (vals[2] << 8) | 0xFF;
	return 0;
}