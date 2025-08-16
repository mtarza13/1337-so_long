/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:59:07 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:51:16 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_characters(t_game *game)
{
	t_count	count;

	count = count_elem(game);
	if (count.num_c < 1 || count.num_e != 1 || count.num_p != 1)
	{
		ft_printf("Error\n=> The map must contain 1 exit,");
		ft_printf(" at least 1 item, and 1 starting position");
		free_map(game);
		exit(EXIT_FAILURE);
	}
	game->total_collect = count.num_c;
}

void	handle_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
		{
			ft_printf("Erreur\n=> La carte doit être encadrée par des murs\n");
			free_map(game);
			exit(EXIT_FAILURE);
		}
		x++;
	}
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		{
			ft_printf("Erreur\n=> La carte doit être encadrée par des murs\n");
			free_map(game);
			exit(EXIT_FAILURE);
		}
		y++;
	}
}

t_count	count_elem(t_game *game)
{
	int		x;
	int		y;
	t_count	count;

	y = 0;
	ft_memset(&count, 0, sizeof(t_count));
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				count.num_c++;
			else if (game->map[y][x] == 'E')
				count.num_e++;
			else if (game->map[y][x] == 'P')
				count.num_p++;
			x++;
		}
		y++;
	}
	return (count);
}
