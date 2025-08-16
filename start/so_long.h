/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:10:22 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:15:07 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		total_collect;
	int		collected;
	int		move;
	void	*player;
	void	*player_front;
	void	*player_back;
	void	*player_left;
	void	*player_right;
	void	*wall_img;
	void	*floor_img;
	void	*collect_img;
	void	*exit_open;
	void	*exit_closed;
	char	prev_tile;

	int		new_x;
	int		new_y;
}			t_game;

typedef struct s_count
{
	int		num_c;
	int		num_e;
	int		num_p;
}			t_count;

typedef struct s_read
{
	int		fd;
	char	*ligne;
	int		i;
	int		h;
}			t_read;

void		read_map(char *file, t_game *game);
void		load_texture(t_game *game);
void		move_player(t_game *game, int x_coordinate, int y_coordinate);
int			handl_key(int keycode, t_game *game);
void		handle_argument(int ac, char *av[]);
void		free_map(t_game *game);
void		handle_characters(t_game *game);
void		handle_paths(t_game *game);
void		handle_walls(t_game *game);
int			exit_game(t_game *game);
void		valid_map(t_game *game);
void		free_map_copy(char **map, int height);
void		render_map(t_game *game);
void		position_player(t_game *game);
t_count		count_elem(t_game *game);

#endif
