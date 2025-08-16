/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:15:11 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 02:17:53 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_sprite(t_game *game, int x_coordinate, int y_coordinate)
{
	if (x_coordinate == 1)
		game->player = game->player_right;
	else if (x_coordinate == -1)
		game->player = game->player_left;
	else if (y_coordinate == 1)
		game->player = game->player_front;
	else if (y_coordinate == -1)
		game->player = game->player_back;
}

void	ft_win(t_game *game)
{
	ft_printf("\033[36mYou completed the game in ");
	ft_printf("\033[1;33m%d\033[0;36m moves!\n", game->move + 1);
	ft_printf("\033[32mYou are a true hero! 🏆\033[0m\n");
	ft_printf("\nThank you for playing! See you soon! 👋\n\n");
	exit_game(game);
}

void	handle_movement(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return ;
	if (game->map[y][x] == 'C')
	{
		game->collected++;
		game->map[y][x] = '0';
	}
	if (game->map[y][x] == 'E')
	{
		if (game->collected == game->total_collect)
			ft_win(game);
		game->new_x = x;
		game->new_y = y;
	}
	if (game->map[game->new_y][game->new_x] == 'P')
		game->map[game->player_y][game->player_x] = 'E';
	else
		game->map[game->player_y][game->player_x] = '0';
	game->player_x = x;
	game->player_y = y;
	game->map[y][x] = 'P';
	game->move++;
}

void	update_display(t_game *game)
{
	char	*move_str;

	move_str = ft_itoa(game->move);
	render_map(game);
	ft_printf("Mouvement : %s\n", move_str);
	free(move_str);
}

void	move_player(t_game *game, int x_coordinate, int y_coordinate)
{
	int	x;
	int	y;

	x = game->player_x + x_coordinate;
	y = game->player_y + y_coordinate;
	update_player_sprite(game, x_coordinate, y_coordinate);
	handle_movement(game, x, y);
	if (game->map[y][x] != '1')
		update_display(game);
}
