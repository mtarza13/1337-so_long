/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 03:34:38 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:34:40 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_textures(t_game *game);

void	free_all(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_textures(game);
	free_map(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	free_textures(t_game *game)
{
	if (game->player_front)
		mlx_destroy_image(game->mlx, game->player_front);
	if (game->player_back)
		mlx_destroy_image(game->mlx, game->player_back);
	if (game->player_left)
		mlx_destroy_image(game->mlx, game->player_left);
	if (game->player_right)
		mlx_destroy_image(game->mlx, game->player_right);
	if (game->collect_img)
		mlx_destroy_image(game->mlx, game->collect_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->exit_closed)
		mlx_destroy_image(game->mlx, game->exit_closed);
	if (game->exit_open)
		mlx_destroy_image(game->mlx, game->exit_open);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
}

void	load_player_textures(t_game *game, int *width, int *height)
{
	game->player_front = mlx_xpm_file_to_image(game->mlx, "./textures/p_do.xpm",
			width, height);
	game->player_back = mlx_xpm_file_to_image(game->mlx, "./textures/p_up.xpm",
			width, height);
	game->player_left = mlx_xpm_file_to_image(game->mlx, "./textures/p_le.xpm",
			width, height);
	game->player_right = mlx_xpm_file_to_image(game->mlx, "./textures/p_ri.xpm",
			width, height);
	game->player = game->player_front;
}

void	load_environment_textures(t_game *game, int *width, int *height)
{
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm",
			width, height);
	game->collect_img = mlx_xpm_file_to_image(game->mlx, "./textures/cer.xpm",
			width, height);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "./textures/col.xpm",
			width, height);
	game->exit_closed = mlx_xpm_file_to_image(game->mlx, "./textures/e_cl.xpm",
			width, height);
	game->exit_open = mlx_xpm_file_to_image(game->mlx, "./textures/e_op.xpm",
			width, height);
}

void	load_texture(t_game *game)
{
	int	width;
	int	height;

	load_player_textures(game, &width, &height);
	load_environment_textures(game, &width, &height);
	if (!game->wall_img || !game->exit_closed || !game->floor_img
		|| !game->collect_img || !game->player_right || !game->player_left
		|| !game->player_back || !game->player_front)
	{
		ft_printf("Error\nFailed to load texture: %s\n",
			"./textures/walll.xpm");
		free_all(game);
		exit(EXIT_FAILURE);
	}
}
