/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:43:03 by sunderle          #+#    #+#             */
/*   Updated: 2020/11/28 19:42:37 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	result;

	i = ft_strlen(dest);
	if (ft_strlen(dest) < size)
		result = i + ft_strlen(src);
	else
		result = size + ft_strlen(src);
	while ((i < size - 1) && (*src) && (size > 0))
		dest[i++] = *(src++);
	dest[i] = 0;
	return (result);
}
