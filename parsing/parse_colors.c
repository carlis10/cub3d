/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:55:17 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/26 20:23:16 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/error.h"
#include "../include/cub3d.h"

static const char	*skip_spaces(const char *p)
{
	while (*p && isspace((unsigned char)*p))
		p++;
	return (p);
}

static int	parse_digits(int val, const char **p, const char *src)
{
	while (**p && isdigit((unsigned char)**p))
	{
		val = (val * 10) + (**p - '0');
		if (val > 255)
			return (set_error(ERR_COLOR_VALUE, src));
		(*p)++;
	}
	return (val);
}

static int	parse_single_val(const char **p, const char *src)
{
	int	val;

	val = 0;
	if (!isdigit((unsigned char)**p))
		return (set_error(ERR_COLOR_FORMAT, src));
	val = parse_digits(val, p, src);
	return (val);
}

static int	validate_end(const char *p, const char *src)
{
	while (*p)
	{
		if (!isspace((unsigned char)*p))
			return (set_error(ERR_COLOR_FORMAT, src));
		p++;
	}
	return (0);
}

static int	parse_component(int *out, const char **p, const char *s, int idx)
{
	int	val;

	val = parse_single_val(p, s);
	if (val < 0)
		return (-1);
	out[idx] = val;
	if (idx < 2)
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
		if (parse_component(vals, &p, s, i) < 0)
			return (-1);
		i++;
	}
	if (validate_end(p, s) < 0)
		return (-1);
	*out_color = (vals[0] << 24)
		| (vals[1] << 16)
		| (vals[2] << 8)
		| 0xFF;
	return (0);
}
