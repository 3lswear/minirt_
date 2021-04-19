/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_bd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:12:18 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:25:10 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_bd(void *dest, const void *src, size_t n, int dir)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (dest == src)
		return (dest);
	if (!dir)
	{
		while (n)
		{
			*d++ = *s++;
			n--;
		}
	}
	else if (dir == 1)
	{
		while (n)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}
