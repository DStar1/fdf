/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:48:05 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 19:06:21 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	t_master	master;
	int			x;
	int			y;

	if (ac == 2)
	{
		master.yrot = 583;
		master.xrot = 0;
		master.wsize = 1000;
		master.xlen = 0;
		master.ylen = 0;
		master.yiter = 0;
		master.xiter = 0;
		master.scale = 1;
		master.coords = points(av[1], &master);
		master.mlx = mlx_init();
		master.win = mlx_new_window(master.mlx,
							master.wsize, master.wsize, av[1]);
		rotate_key(&master);
		scale(&master);
		re_draw(&master);
		mlx_hook(master.win, 2, 0, my_key_funct, &master);
		mlx_hook(master.win, 2, 0, my_key_funct2, &master);
		mlx_loop(master.mlx);
	}
	return (0);
}
