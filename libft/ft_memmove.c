/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:19:13 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/25 19:22:16 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (!dst && !src)
		return (NULL);
	s = src;
	d = dst;
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len--)
			d[len] = s[len];
	}
	return (dst);
}
