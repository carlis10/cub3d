/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:39:07 by carlos            #+#    #+#             */
/*   Updated: 2025/11/25 16:32:15 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	parse_file(argv[1], &game);
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game.mlx)
		return (1);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game.mlx, game.img, 0, 0);

	mlx_loop_hook(game.mlx, hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}


