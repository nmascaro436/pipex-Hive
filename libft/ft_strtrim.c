/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 09:10:16 by nmascaro          #+#    #+#             */
/*   Updated: 2025/04/25 13:20:57 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int		in_set(const char *set, char c);
static size_t	find_start(const char *s1, const char *set);
static size_t	find_end(const char *s1, const char *set);

static int	in_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	find_start(const char *s1, const char *set)
{
	size_t	start;

	start = 0;
	while (s1[start] && in_set(set, s1[start]))
		start++;
	return (start);
}

static size_t	find_end(const char *s1, const char *set)
{
	size_t	end;

	end = ft_strlen(s1);
	while (end > 0 && in_set(set, s1[end -1]))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimstr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	trimstr = (char *) malloc (end - start + 1);
	if (!trimstr)
		return (NULL);
	i = 0;
	while (start < end)
		trimstr[i++] = s1[start++];
	trimstr[i] = '\0';
	return (trimstr);
}
