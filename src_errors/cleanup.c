/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:23:46 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 14:38:50 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"

void	free_map(char **map)
{
	int i;

	if (!map)
		return;
	for (i = 0; map[i]; ++i)
		free(map[i]);
	free(map);
}

void	free_textures(t_game *game)
{
	(void)game;
}

void	destroy_mlx_resources(t_game *game)
{
	(void)game;
}

void	free_game_resources(t_game *game)
{
	if (!game)
		return;
}