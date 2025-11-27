/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:38:13 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/25 15:23:20 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = (char *)ft_calloc(size, sizeof(char));
	if (!s3)
		return (0);
	ft_strlcpy(s3, s1, size);
	ft_strlcat(s3, s2, size);
	return (s3);
}
