/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:01:46 by sunderle          #+#    #+#             */
/*   Updated: 2021/01/23 11:18:48 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_bd(const char *s, int c, int dir)
{
	char	*retval;
	size_t	i;
	size_t	len;

	retval = NULL;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((unsigned char)c == s[i])
			retval = (char *)&s[i];
		if ((dir == 0) && (retval))
			return (retval);
		i++;
	}
	return (retval);
}
