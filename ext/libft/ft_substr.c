/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:03:02 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:21:29 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	result = (char *)ft_calloc((len + 1), sizeof(char));
	if (!len && result)
		return (result);
	else if (result)
		ft_memcpy(result, (char *)&s[start], len);
	return (result);
}
