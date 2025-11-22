/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:29:56 by carlos            #+#    #+#             */
/*   Updated: 2025/11/22 13:41:53 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	d_aux(int map, double pos, int step, double ray_dir)
{
	if (ray_dir == 0)
		return (1e-6);
	return ((map - pos + (1 - step) / 2.0) / ray_dir);
}
