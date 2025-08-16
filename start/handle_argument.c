/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:18:52 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:39:29 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_argument(int argc, char *argv[])
{
	const char	*extension = ".ber";
	int			len;

	if (argc == 2)
	{
		len = ft_strlen(argv[1]);
		if (len <= 4 || ft_strncmp(argv[1] + len - 4, extension, 4) != 0
			|| (argv[1][len - 4] == '.' && argv[1][len - 5] == '/'))
		{
			ft_printf("Error\n=> Invalid argument\n");
			exit(1);
		}
	}
}

int	handl_key(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit_game(game);
	else if (keycode == 'w' || keycode == 65362)
		move_player(game, 0, -1);
	else if (keycode == 's' || keycode == 65364)
		move_player(game, 0, 1);
	else if (keycode == 'a' || keycode == 65361)
		move_player(game, -1, 0);
	else if (keycode == 'd' || keycode == 65363)
		move_player(game, 1, 0);
	return (0);
}
