/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 00:40:09 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 00:40:21 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// Abre y carga las texturas del suelo, monedas, puertas y paredes.
static int	open_ground_coins_door(t_game *game)
{
	game->textures.ground = mlx_xpm_file_to_image(game->mlx, "assets/dirt.xpm",
			&game->width, &game->height);
	if (game->textures.ground == NULL)
		return (1);
	game->textures.coin = mlx_xpm_file_to_image(game->mlx, "assets/coin.xpm",
			&game->width, &game->height);
	if (game->textures.coin == NULL)
		return (1);
	game->textures.door = mlx_xpm_file_to_image(game->mlx, "assets/door.xpm",
			&game->width, &game->height);
	if (game->textures.door == NULL)
		return (1);
	game->textures.wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm",
			&game->width, &game->height);
	if (game->textures.wall == NULL)
		return (1);
	return (0);
}

// Inicializa las dimensiones del juego y carga las imágenes necesarias.
void	open_images(t_game *game)
{
	game->height = HEIGHT;
	game->width = WIDTH;
	game->current_frame = 0;
	game->player.player_idle_right_1 = mlx_xpm_file_to_image(game->mlx,
			"assets/player_idle_right_1.xpm", &game->width, &game->height);
	if (game->player.player_idle_right_1 == NULL)
		return ;
	game->player.player_idle_left_1 = mlx_xpm_file_to_image(game->mlx,
			"assets/player_idle_left_1.xpm", &game->width, &game->height);
	if (game->player.player_idle_left_1 == NULL)
		return ;
	if (open_ground_coins_door(game) == 1)
		write(1, "failed to open the image\n", 25);
}
