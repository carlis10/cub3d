/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:27:48 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/29 14:37:30 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;
	size_t	j;

	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	i = start;
	j = 0;
	if (len > (size_t)ft_strlen(s) || (start + len) > (size_t)ft_strlen(s))
		len = ft_strlen(s) - start;
	r = (char *)ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (0);
	while (s[i] && j < len)
	{
		r[j] = s[i];
		j++;
		i++;
	}
	return (r);
}
