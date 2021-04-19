/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:23:02 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 16:17:35 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	*stop;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	stop = (unsigned char *)ft_memchr(src, (unsigned char)c, n);
	if (stop)
	{
		ft_memcpy(d, s, stop + 1 - s);
		return ((unsigned char *)&d[stop + 1 - s]);
	}
	else
	{
		ft_memcpy(d, s, n);
		return (NULL);
	}
}
