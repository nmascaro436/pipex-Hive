/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:29:33 by nmascaro          #+#    #+#             */
/*   Updated: 2025/04/21 16:11:01 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	i = 0;
	temp = (unsigned char *) malloc(nmemb * size);
	if (!temp)
		return (NULL);
	while (i < (nmemb * size))
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}
