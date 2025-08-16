/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:44:30 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:46:01 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_eof(int j, char **ligne)
{
	if (j == -1)
	{
		free(*ligne);
		return (0);
	}
	if (j == 0)
	{
		if (**ligne == '\0')
		{
			free(*ligne);
			return (0);
		}
		return (1);
	}
	return (-1);
}

static int	ft_ster_bster(int fd, char *tab, char **ligne)
{
	static int	j;
	static int	i;

	if (i >= j)
	{
		j = ft_read_from_fd(fd, tab);
		if (j == -1 || j == 0)
			return (ft_eof(j, ligne));
		i = 0;
	}
	*ligne = ft_append_char(*ligne, tab[i]);
	if (!*ligne)
		return (0);
	if (tab[i] == '\n' || tab[i] == '\0')
	{
		i++;
		return (1);
	}
	i++;
	return (-1);
}

static void	*ft_alloc(void)
{
	char	*ligne;

	ligne = malloc(1);
	if (!ligne)
		return (NULL);
	ligne[0] = '\0';
	return (ligne);
}

char	*get_next_line(int fd)
{
	static char	tab[BUFFER_SIZE + 1];
	char		*ligne;
	int			result;

	result = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ligne = ft_alloc();
	if (!ligne)
		return (NULL);
	while (1)
	{
		result = ft_ster_bster(fd, tab, &ligne);
		if (result == 1)
			break ;
		if (result == 0)
			return (NULL);
	}
	return (ligne);
}
