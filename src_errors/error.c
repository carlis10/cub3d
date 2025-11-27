/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:22:00 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/27 05:51:30 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../include/error.h"

int	set_error(t_error_code code, const char *detail)
{
	char	*s;

	s = (char *)detail;
	if (code <= ERR_NONE || code > ERR_INTERNAL)
		code = ERR_INTERNAL;
	print_error(code, s);
	return (-1);
}

void	print_error(t_error_code code, char *detail)
{
	ft_putstr_fd("error: ", 2);
	if (code <= ERR_NONE || code > ERR_INTERNAL)
		code = ERR_INTERNAL;
	ft_putstr_fd(detail, 2);
	ft_putstr_fd("\n", 2);
}
