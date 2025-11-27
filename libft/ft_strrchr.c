/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:34:39 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/25 17:49:06 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	p;
	int				size;

	p = (unsigned char)c;
	size = ft_strlen(s);
	while (size >= 0)
	{
		if (s[size] == p)
			return ((char *)(s + size));
		size--;
	}
	return (NULL);
}
