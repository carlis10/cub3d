/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:03:14 by cravegli          #+#    #+#             */
/*   Updated: 2025/04/03 13:08:21 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long	r;
	long	s;

	r = 0;
	s = 1;
	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s = -s;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r *= 10;
		r += (char)*str - '0';
		str++;
	}
	r *= s;
	return (r);
}
