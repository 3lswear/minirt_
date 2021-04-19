/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 04:53:33 by sunderle          #+#    #+#             */
/*   Updated: 2021/01/24 14:20:00 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*result;

	if ((nmemb) && ((18446744073709551615UL / nmemb) < size))
		return (NULL);
	total = nmemb * size;
	result = malloc(total);
	if (result)
		ft_bzero(result, total);
	return (result);
}

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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dest || !src)
		return (0);
	src_len = ft_strlen(src);
	i = 0;
	if (size)
	{
		while ((i < size - 1) && (i < src_len))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_len);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(src) + 1;
	dest = (char *)malloc(size * sizeof(char));
	if (dest)
		ft_strlcpy(dest, src, size);
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	s1len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	len = s1len + ft_strlen(s2);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result)
	{
		i = 0;
		while (i < s1len)
		{
			result[i] = s1[i];
			i++;
		}
		while ((i < (len + 1) - 1) && (*s2) && ((len + 1) > 0))
			result[i++] = *(s2++);
		result[i] = 0;
	}
	return (result);
}
