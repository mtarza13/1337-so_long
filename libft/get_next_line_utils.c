/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:45:15 by mtarza            #+#    #+#             */
/*   Updated: 2025/02/27 03:48:42 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_s(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_read_from_fd(int fd, char *tab)
{
	int	count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
	{
		tab[0] = '\0';
		return (-1);
	}
	tab[count] = '\0';
	return (count);
}

char	*ft_append_char(char *ligne, char c)
{
	int		len;
	char	*n_ligne;
	int		i;

	len = ft_strlen_s(ligne);
	n_ligne = malloc(len + 2);
	i = 0;
	if (!n_ligne)
	{
		free(ligne);
		return (NULL);
	}
	while (i < len)
	{
		n_ligne[i] = ligne[i];
		i++;
	}
	n_ligne[len] = c;
	n_ligne[len + 1] = '\0';
	free(ligne);
	return (n_ligne);
}
