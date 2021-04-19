/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 00:11:54 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:11:52 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s)
		return (NULL);
	result = ft_strdup(s);
	i = 0;
	if (result && f)
	{
		while (result[i])
		{
			result[i] = (f)(i, result[i]);
			i++;
		}
	}
	else
		return (NULL);
	return (result);
}
