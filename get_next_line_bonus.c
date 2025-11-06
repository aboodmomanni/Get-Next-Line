/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:00:00 by marvin            #+#    #+#             */
/*   Updated: 2025/10/24 18:26:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	char	*concatonate(char *left, char *buf, int flag)
{
	char	*tmp;

	if (flag == 1)
	{
		free(left);
		return (NULL);
	}
	if (!left)
		return (f_dup(buf));
	tmp = f_join(left, buf);
	if (!tmp)
	{
		free(left);
		return (NULL);
	}
	return (tmp);
}

static char	*readloop(int fd, char *left)
{
	char	*buf;
	int		bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buf);
			return (concatonate(left, NULL, 1));
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		left = concatonate(left, buf, 0);
		if (!left || f_strchr(left, '\n') != -1)
			break ;
	}
	free(buf);
	return (left);
}

static char	*extract_line(char *s)
{
	int		i;
	char	*line;

	if (!s || !s[0])
		return (NULL);
	i = f_strchr(s, '\n');
	if (i == -1)
		i = f_strlen(s);
	else
		i++;
	line = f_ssubstr(s, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_leftover(char *s)
{
	int		start;
	char	*new;

	if (!s)
		return (NULL);
	start = f_strchr(s, '\n');
	if (start == -1)
		return (concatonate(s, NULL, 1));
	start++;
	new = f_ssubstr(s, start, f_strlen(s) - start);
	free(s);
	if (!new || !new[0])
		return (concatonate(new, NULL, 1));
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*leftover[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover[fd] = readloop(fd, leftover[fd]);
	if (!leftover[fd])
		return (NULL);
	line = extract_line(leftover[fd]);
	if (!line)
	{
		free(leftover[fd]);
		return (NULL);
	}
	leftover[fd] = update_leftover(leftover[fd]);
	return (line);
}
