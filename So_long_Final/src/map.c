/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 00:40:32 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 00:40:35 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// Dibuja el mapa del juego en la ventana de MiniLibX,
// basándose en el contenido de una línea del mapa.
void	print_map(char *line, t_game *game, int index)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			mlx_put_image_to_window(game->mlx, game->window,
				game->textures.wall, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == '0')
			mlx_put_image_to_window(game->mlx, game->window,
				game->textures.ground, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == 'C')
			mlx_put_image_to_window(game->mlx, game->window,
				game->textures.coin, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == 'E')
			mlx_put_image_to_window(game->mlx, game->window,
				game->textures.door, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == 'P')
			put_player(game, i, index);
		i++;
	}
}

// Añade los gráficos iniciales al juego dibujando todo el mapa.
void	add_graphics(t_game *game)
{
	int	i;

	i = 0;
	game->score = 0;
	while (game->map[i] != NULL)
	{
		print_map(game->map[i], game, i);
		i++;
	}
}

// Llena el mapa del juego leyendo desde un archivo y valida que sea jugable.
void	fill_map(t_game *game, int lines, char *map)
{
	int	file;
	int	i;

	i = 0;
	file = open(map, O_RDWR);
	game->moves = 0;
	game->player_position = 0;
	game->map = malloc(sizeof(char *) * (lines + 1));
	game->map[0] = get_next_line(file);
	while (i < lines)
	{
		i++;
		game->map[i] = get_next_line(file);
	}
	if (check_map(map, game) == 1)
		exit(EXIT_FAILURE);
	if (valid_path(game) == 1)
	{
		free_map(game);
		write(1, "Error\nNo valid path\n", 20);
		exit(EXIT_FAILURE);
	}
	close(file);
}

int	save_map(char *map, t_game *game)
{
	int		file;
	int		linecount;
	char	*line;

	linecount = 0;
	file = open(map, O_RDWR);
	if (file == -1)
	{
		write(1, "Error\nMap does not exist\n", 25);
		return (1);
	}
	line = get_next_line(file);
	if (line == NULL)
		exit(EXIT_FAILURE);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		linecount++;
	}
	close(file);
	fill_map(game, linecount, map);
	free(line);
	return (0);
}
