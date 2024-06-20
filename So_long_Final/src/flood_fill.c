/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 00:41:32 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 21:25:11 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// Verifica si un movimiento es válido (no es un muro y no ha sido visitado).
int	validmove(t_game *game, int **visited, int row, int col)
{
	return (game->map[row][col] != '1' && !visited[row][col]);
}

// floodfill para contar las monedas accesibles y marcar los caminos visitados.
void	floodfill(t_game *game, int row, int col, int **visited)
{
	if (!validmove(game, visited, row, col) || visited[row][col])
		return ;
	if (game->map[row][col] == 'C')
		game->flood_fill_coins += 1;
	visited[row][col] = 1;
	floodfill(game, row - 1, col, visited);
	floodfill(game, row + 1, col, visited);
	floodfill(game, row, col - 1, visited);
	floodfill(game, row, col + 1, visited);
}

// Encuentra la posición del jugador 'P' en el mapa y actualiza las coordenadas.
void	player_position(t_game *game, int i, int *player_col, int *player_row)
{
	int	j;

	game->flood_fill_coins = 0;
	game->coins = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				*player_row = i;
				*player_col = j;
			}
			j++;
		}
		i++;
	}
}

void	exit_position(t_game *game)
{
	int	j;
	int	i;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E')
			{
				game->exit_row = i;
				game->exit_col = j;
			}
			if (game->map[i][j] == 'C')
				game->coins += 1;
			j++;
		}
		i++;
	}
}

int	valid_path(t_game *game)
{
	int	i;
	int	p_row;
	int	p_col;
	int	**visited;

	visited = ft_calloc(game->map_rows, sizeof(int *));
	i = 0;
	while (i < game->map_rows)
	{
		visited[i] = ft_calloc(game->map_cols, sizeof(int *));
		i++;
	}
	i = 0;
	while (game->map[i])
	{
		player_position(game, i, &p_col, &p_row);
		i++;
	}
	exit_position(game);
	floodfill(game, p_row, p_col, visited);
	i = visited[p_row][p_col] && visited[game->exit_row][game->exit_col];
	free_visited(visited, game);
	if (game->flood_fill_coins != game->coins || !i)
		return (1);
	return (0);
}
