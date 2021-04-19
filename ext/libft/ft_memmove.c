/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 03:07:59 by sunderle          #+#    #+#             */
/*   Updated: 2020/11/25 12:41:54 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return (ft_memcpy_bd(dest, src, n, 1));
	else if (src > dest)
		return (ft_memcpy_bd(dest, src, n, 0));
	else
		return (dest);
}
