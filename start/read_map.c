/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:34:12 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:52:56 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_map_height(char *file, int *expected_width)
{
	int		fd;
	char	*ligne;
	int		height;
	int		line_length;

	fd = open(file, O_RDONLY);
	height = 0;
	if (fd < 0)
		return (-1);
	ligne = get_next_line(fd);
	if (!ligne)
		(ft_printf("Error\n=> The map is empty\n"), exit(1));
	*expected_width = ft_strlen(ligne) - (ligne[ft_strlen(ligne) - 1] == '\n');
	while (ligne)
	{
		line_length = ft_strlen(ligne) - (ligne[ft_strlen(ligne) - 1] == '\n');
		if (line_length != *expected_width)
			(ft_printf("Error\n=> The map must be rectangular\n"),
				free(ligne), close(fd), exit(1));
		height++;
		free(ligne);
		ligne = get_next_line(fd);
	}
	close(fd);
	return (height);
}

void	read_and_allocate_map(char *file, t_game *game, t_read *read)
{
	int	expected_width;
	int	i;

	i = 0;
	read->fd = open(file, O_RDONLY);
	read->i = 0;
	if (read->fd < 0)
		(ft_printf("Erreur\n=> Impossible d'ouvrire le fichier\n"), exit(1));
	game->map_height = count_map_height(file, &expected_width);
	if (game->map_height == 0)
		(ft_printf("Erreur\n=> La carte est vide\n"), exit_game(game));
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
		(ft_printf("Erreur\n=> Allocation de memoire echouer\n"),
			exit_game(game));
	while (i <= game->map_height)
		game->map[i++] = NULL;
}

void	read_lines_into_map(t_game *game, t_read *read)
{
	read->ligne = get_next_line(read->fd);
	while (read->ligne)
	{
		if (read->ligne[0] == '\0')
		{
			ft_printf("Error\n=> Empty line in map\n");
			free(read->ligne);
			exit_game(game);
		}
		if (read->ligne[ft_strlen(read->ligne) - 1] == '\n')
		{
			read->ligne[ft_strlen(read->ligne) - 1] = '\0';
			read->h = 1;
		}
		else
		{
			read->h = 0;
		}
		game->map[read->i] = read->ligne;
		read->i++;
		read->ligne = get_next_line(read->fd);
	}
}

void	read_map(char *file, t_game *game)
{
	t_read	read_map;

	read_and_allocate_map(file, game, &read_map);
	read_lines_into_map(game, &read_map);
	if (read_map.h == 1)
	{
		ft_printf("Error\n=> Empty line at the end of map\n");
		if (game->map)
			free_map(game);
		exit(1);
	}
	game->map[read_map.i] = NULL;
	game->map_width = ft_strlen(game->map[0]);
	handle_characters(game);
	handle_walls(game);
	handle_paths(game);
}

void	position_player(t_game *game)
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
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
