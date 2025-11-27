/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:01:37 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/25 18:38:25 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*l;
	const unsigned char		*t;
	size_t					i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	l = dst;
	t = src;
	while (i < n)
	{
		l[i] = t[i];
		i++;
	}
	return (dst);
}
