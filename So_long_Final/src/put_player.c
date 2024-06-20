/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:45:18 by nate              #+#    #+#             */
/*   Updated: 2024/06/20 00:43:47 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// Función para colocar la imagen del jugador en la ventana
void	put_player(t_game *game, int width, int height)
{
	if (game->player_position == RIGHT)
		mlx_put_image_to_window(game->mlx, game->window,
			game->player.player_idle_right_1, 0 + width * 32, 0 + (height
				* 32));
	else if (game->player_position == LEFT)
		mlx_put_image_to_window(game->mlx, game->window,
			game->player.player_idle_left_1, 0 + width * 32, 0 + (height * 32));
	else if (game->player_position == UP)
		mlx_put_image_to_window(game->mlx, game->window,
			game->player.player_idle_right_1, 0 + width * 32, 0 + (height
				* 32));
	else if (game->player_position == DOWN)
		mlx_put_image_to_window(game->mlx, game->window,
			game->player.player_idle_left_1, 0 + width * 32, 0 + (height * 32));
	game->x = width;
	game->y = height;
}

// Itera sobre cada fila del mapa hasta la penúltima
// comprueba que todos los elementos esten en el mapa
void	check_playable_row(t_game *game, int *c, int *p, int *e)
{
	int	j;
	int	i;

	i = 0;
	while (game->map[i + 1])
	{
		j = 0;
		while (game->map[i][j + 1])
		{
			if (game->map[i][j] == 'C')
				*c = 1;
			if (game->map[i][j] == 'P')
				*p = 1;
			if (game->map[i][j] == 'E')
				*e = 1;
			j++;
		}
		i++;
	}
}
