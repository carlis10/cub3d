/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:55:17 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 02:15:00 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/error.h"
#include "../include/cub3d.h"

const char	*skip_spaces(const char *p)
{
	while (*p && isspace((unsigned char)*p))
		p++;
	return (p);
}

int	parse_single_val(const char **p, const char *src)
{
	int	val;

	val = 0;
	if (!isdigit((unsigned char)**p))
		return (set_error(ERR_COLOR_FORMAT, src));
	while (**p && isdigit((unsigned char)**p))
	{
		val = (val * 10) + (**p - '0');
		if (val > 255)
			return (set_error(ERR_COLOR_VALUE, src));
		(*p)++;
	}
	return (val);
}

int	validate_end(const char *p, const char *src)
{
	while (*p)
	{
		if (!isspace((unsigned char)*p))
			return (set_error(ERR_COLOR_FORMAT, src));
		p++;
	}
	return (0);
}

int	parse_rgb_line_e(int i, const char **p, int vals[3], const char *s)
{
	if (vals[i] < 0)
		return (-1);
	if (i < 2)
	{
		if (**p != ',')
			return (set_error(ERR_COLOR_FORMAT, s));
		(*p)++;
		*p = skip_spaces(*p);
	}
	return (0);
}

int	parse_rgb_line(const char *s, int *out_color)
{
	int			vals[3];
	int			i;
	const char	*p;

	if (!s)
		return (set_error(ERR_COLOR_FORMAT, "empty color"));
	p = skip_spaces(s);
	i = 0;
	while (i < 3)
	{
		vals[i] = parse_single_val(&p, s);
		parse_rgb_line_e(i, &p, vals, s);
		i++;
	}
	if (validate_end(p, s) < 0)
		return (-1);
	*out_color = (vals[0] << 24) | (vals[1] << 16) | (vals[2] << 8) | 0xFF;
	return (0);
}
