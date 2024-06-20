/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 00:41:54 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 00:46:20 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// Gestiona la interacción del jugador con puertas
void	door_locked_right_left(t_game *game, int door_row, int door_col)
{
	if (game->player_position == RIGHT)
	{
		if (game->map[door_row][door_col + 1] == '1')
			return ;
		if (game->map[door_row][door_col + 1] == 'C')
			game->score += 1;
		game->map[door_row][door_col - 1] = '0';
		game->map[door_row][door_col + 1] = 'P';
		put_player(game, door_col + 1, door_row);
		mlx_put_image_to_window(game->mlx, game->window, game->textures.ground,
			(door_col - 1) * 32, door_row * 32);
	}
	else if (game->player_position == LEFT)
	{
		if (game->map[door_row][door_col - 1] == '1')
			return ;
		if (game->map[door_row][door_col - 1] == 'C')
			game->score += 1;
		game->map[door_row][door_col + 1] = '0';
		game->map[door_row][door_col - 1] = 'P';
		put_player(game, door_col - 1, door_row);
		mlx_put_image_to_window(game->mlx, game->window, game->textures.ground,
			(door_col + 1) * 32, door_row * 32);
	}
}

// Gestiona el movimiento del jugador hacia arriba
// Incrementa la puntuación si hay una moneda
// Si hay una salida y todas las monedas están recogidas, finaliza el juego
// Gestiona las puertas bloqueadas cuando se mueve hacia arriba
// Actualiza el número de movimientos y la posición del jugador en el mapa
void	move_top(t_game *game, int i, int j)
{
	game->player_position = UP;
	if (game->map[j + 1][i] == 'C')
		game->score += 1;
	else if (game->map[j + 1][i] == 'E' && game->coins == game->score)
		on_destroy(game);
	else if (game->map[j + 1][i] == 'E')
	{
		door_locked_up_down(game, j + 1, i);
		return ;
	}
	game->moves += 1;
	game->map[j][i] = '0';
	game->map[j + 1][i] = 'P';
	put_player(game, i, j + 1);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.ground, 0
		+ i * 32, 0 + (j * 32));
}

// Gestiona el movimiento del jugador hacia abajo
void	move_down(t_game *game, int i, int j)
{
	game->player_position = DOWN;
	if (game->map[j - 1][i] == 'C')
		game->score += 1;
	else if (game->map[j - 1][i] == 'E' && game->coins == game->score)
		on_destroy(game);
	else if (game->map[j - 1][i] == 'E')
	{
		door_locked_up_down(game, j - 1, i);
		return ;
	}
	game->moves += 1;
	game->map[j][i] = '0';
	game->map[j - 1][i] = 'P';
	put_player(game, i, j - 1);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.ground, 0
		+ i * 32, 0 + (j * 32));
}

// Gestiona el movimiento del jugador hacia la izquierda
void	move_left(t_game *game, int i, int j)
{
	game->player_position = LEFT;
	if (game->map[j][i - 1] == 'C')
		game->score += 1;
	else if (game->map[j][i - 1] == 'E' && game->coins == game->score)
		on_destroy(game);
	else if (game->map[j][i - 1] == 'E')
	{
		door_locked_right_left(game, j, i - 1);
		return ;
	}
	game->moves += 1;
	game->map[j][i] = '0';
	game->map[j][i - 1] = 'P';
	put_player(game, i - 1, j);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.ground, 0
		+ i * 32, 0 + (j * 32));
}

// Gestiona el movimiento del jugador hacia la derecha
void	move_right(t_game *game, int i, int j)
{
	game->player_position = RIGHT;
	if (game->map[j][i + 1] == 'C')
		game->score += 1;
	else if (game->map[j][i + 1] == 'E' && game->coins == game->score)
		on_destroy(game);
	else if (game->map[j][i + 1] == 'E')
	{
		door_locked_right_left(game, j, i + 1);
		return ;
	}
	game->moves += 1;
	game->map[j][i] = '0';
	game->map[j][i + 1] = 'P';
	put_player(game, i + 1, j);
	mlx_put_image_to_window(game->mlx, game->window, game->textures.ground, 0
		+ i * 32, 0 + (j * 32));
}
