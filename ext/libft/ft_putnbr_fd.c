/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:54:33 by sunderle          #+#    #+#             */
/*   Updated: 2021/04/19 18:22:16 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_round_dec(int n)
{
	int	decimal;

	decimal = 1;
	while ((n / decimal >= 10) || (n / decimal <= -10))
		decimal *= 10;
	return (decimal);
}

void	ft_putnbr_fd(int num, int fd)
{
	char	digit;
	int		power;

	power = get_round_dec(num);
	if (num < 0)
		ft_putchar_fd('-', fd);
	while (power >= 1)
	{
		digit = num / power;
		if (num < 0)
			digit = -digit;
		ft_putchar_fd(digit + '0', fd);
		num -= (power * (num / power));
		power /= 10;
	}
}
