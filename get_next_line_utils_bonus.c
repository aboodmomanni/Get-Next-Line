/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmoman <aalmoman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 06:05:40 by marvin            #+#    #+#             */
/*   Updated: 2025/09/08 20:05:04 by aalmoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	f_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	f_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*f_dup(char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = f_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < len)
		dup[i] = s[i];
	dup[len] = '\0';
	return (dup);
}

char	*f_join(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*joined;
	size_t	i;

	s1len = f_strlen(s1);
	s2len = f_strlen(s2);
	i = 0;
	joined = (char *)malloc(s1len + s2len + 1);
	if (!joined)
		return (NULL);
	while (i < s1len)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i < s1len + s2len)
	{
		joined[i] = s2[i - s1len];
		i++;
	}
	joined[i] = '\0';
	free(s1);
	return (joined);
}

char	*f_ssubstr(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = f_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < len)
		sub[i] = s[start + i];
	sub[len] = '\0';
	return (sub);
}
