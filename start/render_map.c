/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:04:58 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 02:28:01 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	valid_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] != '1' && game->map[y][x] != '0'
				&& game->map[y][x] != 'C' && game->map[y][x] != 'E'
				&& game->map[y][x] != 'P')
			{
				ft_printf("Erreur : Caractère invalide dans la carte.\n");
				free_map(game);
				exit(1);
			}
			x++;
		}
		y++;
	}
}

void	img_ren(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player, x * 32, y
			* 32);
	else if (game->collected == game->total_collect)
		mlx_put_image_to_window(game->mlx, game->win, game->exit_open, x * 32, y
			* 32);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->exit_closed, x * 32,
			y * 32);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor_img, x
				* 32, y * 32);
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x
					* 32, y * 32);
			else if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collect_img,
					x * 32, y * 32);
			else if (game->map[y][x] == 'E' || game->map[y][x] == 'P')
				img_ren(game, x, y);
			x++;
		}
		y++;
	}
}
