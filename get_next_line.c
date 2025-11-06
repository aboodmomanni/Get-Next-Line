/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmoman <aalmoman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:49:02 by aalmoman          #+#    #+#             */
/*   Updated: 2025/10/19 18:49:02 by aalmoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = readloop(fd, leftover);
	if (!leftover)
		return (NULL);
	line = extract_line(leftover);
	if (!line)
	{
		free(leftover);
		return (NULL);
	}
	leftover = update_leftover(leftover);
	return (line);
}
/*
 int main()
 {
 	int fd = open("get_next_line.h", O_RDONLY);
 	char *line;
 	while ((line = get_next_line(fd)))
 	{
 		printf("%s\n", line);
 		free(line);
 	}
 	close(fd);
 	return (0);
 }*/
