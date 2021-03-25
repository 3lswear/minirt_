/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 22:23:19 by sunderle          #+#    #+#             */
/*   Updated: 2021/03/25 22:23:22 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../includes/minirt.h"

int	main(void)
{
	t_win window;

    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, 1366, 768, "jopa");
    mlx_loop(window.mlx);
	return (0);
}      
