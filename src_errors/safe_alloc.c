/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:24:09 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 14:59:17 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/error.h"

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