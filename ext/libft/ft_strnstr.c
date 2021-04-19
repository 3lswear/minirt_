/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 18:20:10 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:25:39 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_size;
	size_t	i;

	n_size = ft_strlen(needle);
	if (!n_size)
		return ((char *)haystack);
	if (n_size > len && haystack)
		return (NULL);
	i = 0;
	while ((i <= len - n_size) && (haystack[i]))
	{
		if (!ft_strncmp(needle, &haystack[i], n_size))
			return ((char *)&(haystack)[i]);
		i++;
	}
	return (NULL);
}
