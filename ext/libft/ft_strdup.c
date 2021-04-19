/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:57:04 by sunderle          #+#    #+#             */
/*   Updated: 2020/11/24 00:15:41 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(src) + 1;
	dest = (char *)malloc(size * sizeof(char));
	if (dest)
		ft_strlcpy(dest, src, size);
	return (dest);
}
