/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javierzaragozatejeda <javierzaragozatej    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:20:32 by javierzarag       #+#    #+#             */
/*   Updated: 2025/11/22 14:38:54 by javierzarag      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "cub3d.h"
# include <stddef.h>

typedef enum e_error_code
{
	ERR_NONE = 0,
	ERR_USAGE,
	ERR_BAD_EXTENSION,
	ERR_OPEN_FILE,
	ERR_READ_FILE,
	ERR_DUP_ID,
	ERR_MISSING_ID,
	ERR_TEXTURE_OPEN,
	ERR_TEXTURE_LOAD,
	ERR_COLOR_FORMAT,
	ERR_COLOR_VALUE,
	ERR_MAP_INVALID,
	ERR_MAP_NOT_CLOSED,
	ERR_INVALID_CHAR,
	ERR_PLAYER_COUNT,
	ERR_MALLOC,
	ERR_MLX_INIT,
	ERR_INTERNAL
}	t_error_code;


int		set_error(t_error_code code, const char *detail, t_game *game);


void	print_error(t_error_code code, const char *detail);


void	error_exit(t_error_code code, const char *detail, t_game *game);


void	*xmalloc(size_t size, t_game *game);


void	free_game_resources(t_game *game);

#endif