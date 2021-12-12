/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pforesti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:20:27 by pforesti          #+#    #+#             */
/*   Updated: 2021/11/07 08:42:03 by pforesti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_fill_rtn_str(char *buffer, int *i)
{
	static char	*rtn_str;
	char		*current;
	static int	state = 0;

	if (!state)
		rtn_str = ft_substr_gnl(buffer, *i, ft_strlen_gnl(buffer + *i, 1));
	else
	{
		current = ft_substr_gnl(buffer, *i, ft_strlen_gnl(buffer + *i, 1));
		rtn_str = ft_strjoin_gnl(rtn_str, current);
	}
	if (!(ft_isnlended(rtn_str)))
		state = 1;
	else
		state = 0;
	*i += ft_strlen_gnl((buffer + *i), 1);
	return (rtn_str);
}

char	*get_next_line(int fd)
{
	static int		value_read = 1;
	static int		index = 0;
	static char		buffer[BUFFER_SIZE];
	char			*rtn_str;

	if (read(fd, buffer, 0) < 0 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	rtn_str = NULL;
	while (!(ft_isnlended(rtn_str)) && value_read)
	{
		if (!index)
			value_read = read(fd, buffer, BUFFER_SIZE);
		if (value_read)
			rtn_str = ft_fill_rtn_str(buffer, &index);
		if (index >= BUFFER_SIZE)
			ft_clear(buffer, &index);
	}
	if (!rtn_str || !ft_strlen_gnl(rtn_str, 0))
	{
		free((void *)rtn_str);
		return (NULL);
	}
	return (rtn_str);
}
