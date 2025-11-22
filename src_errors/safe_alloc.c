/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:24:09 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 14:37:36 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"

void	*xmalloc(size_t size, t_game *game)
{
	void *p;

	p = malloc(size);
	if (!p)
	{
		set_error(ERR_MALLOC, "malloc failed", game);
		return (NULL);
	}
	return (p);
}