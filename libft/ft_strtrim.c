/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:39:42 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/27 16:01:31 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countstart(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	res;
	int	o;

	i = 0;
	j = 0;
	o = 0;
	res = 0;
	while (s1[i] && o == 0)
	{
		o = 1;
		while (set[j] && o == 1)
		{
			if (set[j] == s1[i])
			{
				res++;
				o = 0;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (res);
}

int	ft_countend(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	res;
	int	o;

	i = ft_strlen(s1) - 1;
	j = 0;
	o = 0;
	res = 0;
	while (i > 0 && o == 0)
	{
		o = 1;
		while (set[j] && o == 1)
		{
			if (set[j] == s1[i])
			{
				res++;
				o = 0;
			}
			j++;
		}
		j = 0;
		i--;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*r;
	int		s;
	int		e;
	int		t;

	s = ft_countstart(s1, set);
	if (s == ft_strlen(s1))
		return (ft_strdup(""));
	e = ft_countend(s1, set);
	t = s + e;
	r = ft_substr(s1, s, ft_strlen(s1) - t);
	return (r);
}
