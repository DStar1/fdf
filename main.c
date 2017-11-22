/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:48:05 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 23:06:23 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	t_master	m;
	int			x;
	int			y;

	if (ac == 2)
	{
		m.yrot = 583;
		m.xrot = 0;
		m.wsize = 1000;
		m.xlen = 0;
		m.ylen = 0;
		m.yiter = 0;
		m.xiter = 0;
		m.scale = 1;
		m.coords = points(av[1], &m);
		m.mlx = mlx_init();
		m.win = mlx_new_window(m.mlx, m.wsize, m.wsize, av[1]);
		EXIT(m.wsize <= 0);
		rotate_key(&m);
		scale(&m);
		re_draw(&m);
		mlx_hook(m.win, 2, 0, my_key_funct, &m);
		mlx_loop(m.mlx);
	}
	return (0);
}
