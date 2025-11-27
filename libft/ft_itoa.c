/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:46:23 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/27 18:32:12 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intsize(long int n)
{
	int	s;

	s = 0;
	if (n < 0)
	{
		n = -n;
		s++;
	}
	if (n == 0)
		s++;
	while (n > 0)
	{
		n = n / 10;
		s++;
	}
	return (s);
}

char	*fill_str(char *c, long int n, int s)
{
	c[s] = 0;
	s--;
	if (n == 0)
		c[0] = '0';
	else
	{
		if (n < 0)
		{
			c[0] = '-';
			n = -n;
		}
		while (n > 0)
		{
			c[s] = (n % 10) + '0';
			n = n / 10;
			s--;
		}
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int			s;
	char		*c;

	s = ft_intsize(n);
	c = (char *)malloc((s + 1) * sizeof(char));
	if (!c)
		return (NULL);
	c = fill_str(c, n, s);
	return (c);
}
