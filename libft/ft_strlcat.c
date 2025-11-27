/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:00:18 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/25 16:42:38 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	j = d_len;
	i = 0;
	if (dstsize <= d_len)
		return (s_len + dstsize);
	while (src[i] && (d_len + i) < (dstsize - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = 0;
	if (dstsize < d_len)
		d_len = dstsize;
	return (d_len + s_len);
}
