/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Carlos <Carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:16:39 by cravegli          #+#    #+#             */
/*   Updated: 2023/09/27 19:04:01 by Carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nl;
	char		c;

	nl = n;
	if (nl < 0)
	{
		nl = -nl;
		ft_putchar_fd('-', fd);
	}
	if (nl > 9)
	{
		ft_putnbr_fd(nl / 10, fd);
		ft_putnbr_fd(nl % 10, fd);
	}
	else
	{
		c = nl + '0';
		ft_putchar_fd(c, fd);
	}
}
