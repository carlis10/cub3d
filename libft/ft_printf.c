/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:04:35 by cravegli          #+#    #+#             */
/*   Updated: 2024/01/29 13:02:13 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_arg(char chr, va_list ap, size_t count)
{
	if (chr == 'c')
		count = print_chr((char) va_arg(ap, int));
	else if (chr == 's')
		count = print_str(va_arg(ap, char *));
	else if (chr == 'p')
		count = print_void(ap);
	else if (chr == 'd' || chr == 'i')
		count = ft_putnbr_fd_pr(va_arg(ap, int), 1, 0);
	else if (chr == 'u')
		count = ft_putnbr_fd_pr_unint(va_arg(ap, unsigned int), 1, 0);
	else if (chr == 'x')
		count = ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef", 0);
	else if (chr == 'X')
		count = ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF", 0);
	else if (chr == '%')
	{
		ft_putchar_fd(chr, 1);
		count++;
	}
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	size_t	count;
	int		i;

	if (!str)
		return (0);
	i = 0;
	va_start(ap, str);
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += read_arg(str[i + 1], ap, 0);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			count++;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
