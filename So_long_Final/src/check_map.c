/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:09:44 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 00:42:12 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"

// que la última fila del mapa esté compuesta únicamente por '1' = muros
static int	check_last_row(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
		{
			write(1, "Error\nLast row has to contain only walls\n", 41);
			return (1);
		}
		i++;
	}
	return (0);
}

// Comprueba las filas del mapa que estén correctamente cerradas con muros
static int	check_rows(t_game *game, int linecount)
{
	int	row_len;
	int	i;

	row_len = 0;
	while (game->map[0][row_len + 1])
	{
		if (game->map[0][row_len] != '1')
			return (1);
		row_len++;
	}
	if (row_len < 3)
		return (1);
	i = 0;
	while (game->map[i + 1])
	{
		if (ft_strlen(game->map[i]) < (size_t)game->map_cols
			|| (game->map[i][row_len] && i + 1 == linecount))
			return (1);
		if (game->map[i][row_len + 1] || !(game->map[i][row_len - 1]))
			return (1);
		if (game->map[i][0] != '1' || game->map[i][row_len - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

// Verifica elementos esenciales en el mapa (jugadores,salidas,etc.)
static int	check_elements(t_game *game)
{
	int	i;
	int	p;
	int	e;

	i = 0;
	p = 0;
	e = 0;
	while (game->map[i])
	{
		if (check_char(game, &p, &e, i) == 1)
			return (1);
		i++;
	}
	return (0);
}

// Realiza una serie de verificaciones avanzadas sobre el mapa
static int	advanced_checks(t_game *game, int linecount, char *map)
{
	if (check_filename(map) == 1)
		return (1);
	if (check_last_row(game->map[linecount - 1]) == 1)
		return (1);
	if (check_rows(game, linecount) == 1)
	{
		write(1, "Error\nThe map must be el mapa debe estar rodeado/ cerrado\n",
			59);
		return (1);
	}
	if (check_elements(game) == 1)
	{
		write(1, "Error\nAl mapa le faltan cosas\n", 31);
		return (1);
	}
	if (check_playable(game) == 1)
	{
		write(1, "Error\nEl mapa no es valido", 27);
		return (1);
	}
	if (check_last_row_rectan(game) == 1)
		return (1);
	return (0);
}

// chequea el largo de las filas y columnas del mapa
int	check_map(char *map, t_game *game)
{
	int	linecount;
	int	colcount;

	linecount = 0;
	colcount = 0;
	while (game->map[linecount])
		linecount++;
	while (game->map[0][colcount])
		colcount++;
	game->map_cols = colcount;
	game->map_rows = linecount - 1;
	if (advanced_checks(game, linecount, map) == 1)
	{
		return (1);
	}
	return (0);
}
