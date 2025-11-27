/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 03:13:11 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 05:07:14 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/cub3d.h"
#include "../include/error.h"

char	*fill_line(char *l)
{
	char	*line;
	int		i;

	line = ft_calloc(sizeof(char), ft_strlen(l));
	i = 0;
	while (l[i] && l[i] != '\n')
	{
		line[i] = l[i];
		i++;
	}
	free(l);
	return (line);
}

char	**first_map_alloc(char **arr, int count, const char *filename)
{
	int		i;
	char	*line;
	int		f;

	i = 0;
	arr = ft_calloc(sizeof(char *), (count + 1));
	f = open(filename, 0);
	line = get_next_line(f);
	while (line)
	{
		arr[i] = fill_line(line);
		i++;
		count++;
		line = get_next_line(f);
	}
	return (arr);
}

int	read_all_l(const char *fname, char ***out_lines, int *out_c)
{
	int		f;
	char	**arr;
	int		count;
	char	*line;

	f = open(fname, 0);
	if (!f)
		return (set_error(ERR_OPEN_FILE, fname));
	arr = NULL;
	count = 0;
	line = get_next_line(f);
	while (line)
	{
		count++;
		line = get_next_line(f);
	}
	close(f);
	arr = first_map_alloc(arr, count, fname);
	if (count == 0)
		return (set_error(ERR_READ_FILE, "file is empty"));
	*out_lines = arr;
	*out_c = count;
	return (0);
}
