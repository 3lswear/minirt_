/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 21:25:35 by sunderle          #+#    #+#             */
/*   Updated: 2020/11/27 15:36:47 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*result;

	if ((nmemb) && ((FT_SIZE_MAX / nmemb) < size))
		return (NULL);
	total = nmemb * size;
	result = malloc(total);
	if (result)
		ft_bzero(result, total);
	return (result);
}
