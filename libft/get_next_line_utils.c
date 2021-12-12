/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:58:36 by pforesti          #+#    #+#             */
/*   Updated: 2021/11/07 08:43:18 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_clear(char *buffer, int *index)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
	*index = 0;
}

size_t	ft_isnlended(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen_gnl(char const *s, int flag)
{
	int	i;

	i = 0;
	if (flag)
	{
		while (i < BUFFER_SIZE && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			return (i + 1);
	}
	else
		while (s[i])
			i++;
	return (i);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	if (start + len > ft_strlen_gnl(s, 0))
		len = ft_strlen_gnl(s, 0) - start;
	dest = malloc(len + 1 * sizeof(*dest));
	if (!dest)
		return (NULL);
	i = 0;
	while (*s && i < len)
	{
		dest[i] = *(s + start + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*d;
	int		i;
	int		j;

	d = malloc((ft_strlen_gnl(s1, 0) + ft_strlen_gnl(s2, 0) + 1) * sizeof(*d));
	if (!d)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
	{
		d[j] = s1[i];
		j++;
	}
	i = -1;
	while (s2[++i])
	{
		d[j] = s2[i];
		j++;
	}
	d[j] = '\0';
	free((void *)s1);
	free((void *)s2);
	return (d);
}
