/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:57:48 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 06:31:09 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/error.h"
#include "../include/cub3d.h"

int	is_blank_line(const char *s)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (!isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

int	append_map_line(t_game *g, const char *src)
{
	char	**tmp;
	char	*dup;

	dup = ft_strdup(src);
	if (!dup)
		return (set_error(ERR_MALLOC, "map duplicate"));
	tmp = realloc(g->map_lines, sizeof(char *) * (g->m_h + 1));
	if (!tmp)
	{
		free(dup);
		return (set_error(ERR_MALLOC, "map lines"));
	}
	g->map_lines = tmp;
	(g->map_lines)[g->m_h] = dup;
	g->m_h++;
	return (0);
}

int	process_map_lines(char **file_lines, int nlines, int start, t_game *g)
{
	int		i;
	int		len;

	i = start;
	while (i < nlines)
	{
		if (is_blank_line(file_lines[i]))
			break ;
		len = strlen(file_lines[i]);
		if (len > g->m_w)
			g->m_w = len;
		if (append_map_line(g, file_lines[i]) != 0)
		{
			free_map_lines(g->map_lines, g->m_h);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	extract_m_b(char **f_l, int nlines, int s_i, t_game *g)
{
	int		i;

	i = s_i;
	g->m_h = 0;
	g->m_w = 0;
	while (i < nlines && is_blank_line(f_l[i]))
		i++;
	if (i >= nlines)
		return (set_error(ERR_MAP_INVALID,
				"map missing after identifiers"));
	if (process_map_lines(f_l, nlines, i, g) != 0)
		return (-1);
	if (g->m_h == 0)
	{
		free(g->map_lines);
		return (set_error(ERR_MAP_INVALID, "map missing"));
	}
	return (0);
}
