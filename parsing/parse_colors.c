/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:55:17 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/23 00:38:54 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "include/error.h"
#include "include/cub3d.h"

static const char	*skip_spaces(const char *p)
{
	while (*p && isspace((unsigned char)*p))
		p++;
	return (p);
}

static int	parse_single_val(const char **p, t_game *game, const char *src)
{
	int	val;

	val = 0;
	if (!isdigit((unsigned char)**p))
		return (set_error(ERR_COLOR_FORMAT, src, game));
	while (**p && isdigit((unsigned char)**p))
	{
		val = (val * 10) + (**p - '0');
		if (val > 255)
			return (set_error(ERR_COLOR_VALUE, src, game));
		(*p)++;
	}
	return (val);
}

static int	validate_end(const char *p, const char *src, t_game *game)
{
	while (*p)
	{
		if (!isspace((unsigned char)*p))
			return (set_error(ERR_COLOR_FORMAT, src, game));
		p++;
	}
	return (0);
}

int	parse_rgb_line(const char *s, int *out_color, t_game *game)
{
	int			vals[3];
	int			i;
	const char	*p;

	if (!s)
		return (set_error(ERR_COLOR_FORMAT, "empty color", game));
	p = skip_spaces(s);
	i = 0;
	while (i < 3)
	{
		vals[i] = parse_single_val(&p, game, s);
		if (vals[i] < 0)
			return (-1);
		if (i < 2)
		{
			if (*p != ',')
				return (set_error(ERR_COLOR_FORMAT, s, game));
			p++;
			p = skip_spaces(p);
		}
		i++;
	}
	if (validate_end(p, s, game) < 0)
		return (-1);
	*out_color = (vals[0] << 24) | (vals[1] << 16) | (vals[2] << 8) | 0xFF;
	return (0);
}