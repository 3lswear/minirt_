/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 02:56:21 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:23:13 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				retval;
	unsigned int	count;

	count = 0;
	retval = 0;
	while (count++ < n)
	{
		retval = ((unsigned char *)s1)[count - 1] - ((unsigned char *)s2)
		[count - 1];
		if (retval)
			return (retval);
	}
	return (retval);
}
