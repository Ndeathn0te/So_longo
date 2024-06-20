/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:31:16 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 00:35:22 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// Función para limpiar y liberar todos los recursos antes de cerrar el juego.
int	on_destroy(t_game *game)
{
	free_map(game);
	free_player(game);
	free_textures(game);
	mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

// Función para actualizar la posición del jugador según la tecla presionada.
// Convierte el número de movimientos a cadena y lo escribe en la salida.
// Verifica la letra y actualiza la posición si el movimiento es válido.
void	update_player_position(t_game *game, int key)
{
	int		i;
	int		j;
	char	*moves;

	i = game->x;
	j = game->y;
	moves = ft_itoa(game->moves);
	write(1, moves, ft_strlen(moves));
	write(1, "\n", 1);
	free(moves);
	if (key == 's' && game->map[j + 1][i] != '1')
		move_top(game, i, j);
	else if (key == 'w' && game->map[j - 1][i] != '1')
		move_down(game, i, j);
	else if (key == 'a' && game->map[j][i - 1] != '1')
		move_left(game, i, j);
	else if (key == 'd' && game->map[j][i + 1] != '1')
		move_right(game, i, j);
}

// Manejador de eventos de teclado.
// Si la tecla presionada es Escape (código 65307) cierra
// Actualiza la posición del jugador
int	key_hook(int keycode, t_game *game)
{
	if (keycode == 'w' || keycode == 's' || keycode == 'd' || keycode == 'a')
		update_player_position(game, keycode);
	else if (keycode == 65307)
		on_destroy(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (save_map(argv[1], &game) == 1)
			exit(EXIT_FAILURE);
		game.mlx = mlx_init();
		game.window = mlx_new_window(game.mlx, (game.map_cols - 1) * 32,
				(game.map_rows + 1) * 32, "so_long");
		open_images(&game);
		add_graphics(&game);
		mlx_key_hook(game.window, key_hook, &game);
		mlx_hook(game.window, 17, 0, on_destroy, &game);
		mlx_loop(game.mlx);
	}
	else
	{
		write(1, "solo un argumento\n", 19);
	}
	exit(EXIT_SUCCESS);
}
