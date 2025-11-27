/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:29:56 by carlos            #+#    #+#             */
/*   Updated: 2025/11/27 01:04:26 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	d_aux(int map, double pos, int step, double ray_dir)
{
	if (ray_dir == 0)
		return (1e-6);
	return ((map - pos + (1 - step) / 2.0) / ray_dir);
}

int	check_hit(t_game *g)
{
	if (g->r.m_x < 0 || g->r.m_x >= g->m_w
		|| g->r.m_y < 0 || g->r.m_y >= g->m_h)
		return (0);
	return (1);
}
