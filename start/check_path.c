/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:44:39 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:14:55 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || map[y] == NULL || map[y][x] == '\0')
		return ;
	if (map[y][x] == '1' || map[y][x] == 'A')
		return ;
	map[y][x] = 'A';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static void	check_path(char **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
			{
				ft_printf("Error\nNo valid path to collectibles or exit\n");
				free_map_copy(map, game->map_height);
				free_map(game);
				exit(EXIT_FAILURE);
			}
			x++;
		}
		free(map[y]);
		y++;
	}
	free(map);
}

static char	**create_map_copy(t_game *game)
{
	char	**map_copy;
	int		y;

	map_copy = malloc(sizeof(char *) * game->map_height);
	if (!map_copy)
	{
		ft_printf("Error\nMemory allocation failed\n");
		free_map(game);
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < game->map_height)
	{
		map_copy[y] = ft_strdup(game->map[y]);
		if (!map_copy[y])
		{
			ft_printf("Error\nMemory allocation failed\n");
			free_map_copy(map_copy, y);
			free_map(game);
			exit(EXIT_FAILURE);
		}
		y++;
	}
	return (map_copy);
}

static void	perform_flood_fill(char **map_copy, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				flood_fill(map_copy, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	handle_paths(t_game *game)
{
	char	**map_copy;

	map_copy = create_map_copy(game);
	perform_flood_fill(map_copy, game);
	check_path(map_copy, game);
}
