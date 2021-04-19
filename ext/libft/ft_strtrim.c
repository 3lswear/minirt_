/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:37:02 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:21:00 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char const *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;
	const char	*str;

	str = s1;
	start = 0;
	if (!s1)
		return (NULL);
	while (str[start] && ft_in_set(set, str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (str[end] && ft_in_set(set, str[end]))
		end--;
	return (ft_substr(str, start, end - start + 1));
}
