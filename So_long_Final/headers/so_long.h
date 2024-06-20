/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armgonza <armgonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 21:23:20 by armgonza          #+#    #+#             */
/*   Updated: 2024/06/20 21:23:30 by armgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WIDTH 32  
# define HEIGHT 32 
# define RIGHT 0
# define LEFT 1
# define UP 2
# define DOWN 3

# include "../get_next_line/get_next_line.h"
# include "mlx.h"
// MiniLibX
# include <fcntl.h>
// abrir cosas
# include <stdint.h>
// GNL REAAAAAAAD
# include <stdlib.h> // IMALLOCAAAAA
# include <time.h> // no lo use :,) XD
# include <unistd.h> // WRITAAAA
// Estructura para almacenar las imágenes del jugador
typedef struct s_player
{
	void		*player_idle_right_1;
	void		*player_idle_left_1;
}				t_player;

// Estructura para almacenar las texturas del juego
typedef struct s_textures
{
	void		*ground;
	void		*coin;
	void		*door;
	void		*wall;
}				t_textures;

// Estructura principal del juego que contiene todos los datos necesarios
typedef struct s_game
{
	void		*mlx;
	void		*window;
	int			score;
	int			coins;
	int			moves;
	int			width;
	int			height;
	int			x;
	int			y;
	int			map_rows;
	int			map_cols;
	int			exit_row;
	int			exit_col;
	int			flood_fill_coins;
	int			current_frame;
	int			player_position;
	char		**map;
	t_textures	textures;
	t_player	player;
}				t_game;

char			*ft_itoa(int n);
int				on_destroy(t_game *game);
int				save_map(char *map, t_game *game);
void			open_images(t_game *game);
void			add_graphics(t_game *game);
void			put_player(t_game *game, int width, int height);
void			open_score(t_game *game);
void			door_locked_up_down(t_game *game, int door_row, int door_col);
void			move_top(t_game *game, int i, int j);
void			move_down(t_game *game, int i, int j);
void			move_right(t_game *game, int i, int j);
void			move_left(t_game *game, int i, int j);
void			free_map(t_game *game);
void			free_player(t_game *game);
void			free_textures(t_game *game);
void			free_visited(int **visited, t_game *game);
int				check_playable(t_game *game);
int				check_filename(char *file);
int				check_map(char *map, t_game *game);
int				valid_path(t_game *game);
int				check_char(t_game *game, int *p, int *e, int i);
int				check_last_row_rectan(t_game *game);
void			check_playable_row(t_game *game, int *c, int *p, int *e);

#endif
