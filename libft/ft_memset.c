/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:53:45 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/22 14:18:03 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*l;
	size_t			i;

	i = 0;
	l = s;
	while (i < len)
	{
		l[i] = (unsigned char) c;
		i++;
	}
	return (s);
}
