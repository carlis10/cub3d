/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos <carlos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:39:07 by carlos            #+#    #+#             */
/*   Updated: 2025/11/19 19:08:19 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"


int main(void)
{
	t_game game;
	
	int base[M_H][M_W] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,1},
		{1,0,0,0,0,0,1,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
	for (int y = 0; y < M_H; y++)
		for (int x = 0; x < M_W; x++)
			game.map[y][x] = base[y][x];
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game.mlx)
		return (1);
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	game.p = (t_player){4.5, 3.5, -1, 0, 0, 0.66};

	game.wall_tex[0] = mlx_load_png("pics/bluestone.png");
	check_texture(game.wall_tex[0], "pics/bluestone.png");
	game.wall_tex[1] = mlx_load_png("pics/colorstone.png");
	check_texture(game.wall_tex[1], "pics/colorstone.png");
	game.wall_tex[2] = mlx_load_png("pics/wood.png");
	check_texture(game.wall_tex[2], "pics/wood.png");
	game.wall_tex[3] = mlx_load_png("pics/pillar.png");
	check_texture(game.wall_tex[3], "pics/pillar.png");

	mlx_loop_hook(game.mlx, hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}


