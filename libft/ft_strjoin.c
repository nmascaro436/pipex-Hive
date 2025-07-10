/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:28:26 by nmascaro          #+#    #+#             */
/*   Updated: 2025/04/23 14:44:46 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinedstr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	joinedstr = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinedstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joinedstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joinedstr[j++] = s2[i++];
	joinedstr[j] = '\0';
	return (joinedstr);
}
