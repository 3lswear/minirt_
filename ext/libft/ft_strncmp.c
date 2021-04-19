/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 15:54:55 by sunderle          #+#    #+#             */
/*   Updated: 2020/11/25 14:53:50 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char	*string1;
	const char	*string2;
	size_t		count;
	int			retval;

	string1 = s1;
	string2 = s2;
	count = n;
	retval = 0;
	while (count > 0)
	{
		if (*string1 != '\0' || *string2 != '\0')
		{
			retval = ((unsigned char)*string1 - (unsigned char)*string2);
			if (retval)
				return (retval);
		}
		else
			break ;
		string1++;
		string2++;
		count--;
	}
	return (retval);
}
