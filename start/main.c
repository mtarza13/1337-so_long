/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:12:53 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:13:33 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game->map)
		return ;
	i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
}

void	initialize_game(int ac, char *av[], t_game *game)
{
	if (ac != 2)
	{
		ft_printf("Error\n=> Map file must be specified .ber format\n");
		exit(1);
	}
	ft_memset(game, 0, sizeof(t_game));
	handle_argument(ac, av);
	read_map(av[1], game);
	valid_map(game);
	position_player(game);
	game->move = 0;
}

void	setup_window(t_game *game)
{
	int	win_width;
	int	win_height;

	win_width = game->map_width * 32;
	win_height = game->map_height * 32;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, win_width, win_height,
			"So_long (mtarza)");
	load_texture(game);
	render_map(game);
}

void	setup_hooks(t_game *game)
{
	mlx_key_hook(game->win, handl_key, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char *av[])
{
	t_game	game;

	initialize_game(ac, av, &game);
	setup_window(&game);
	setup_hooks(&game);
	return (0);
}
