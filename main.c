/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:48:05 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 15:33:14 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int ac, char **av)
{
	//t_points **coords;
	t_master master;
	int x;
	int y;
	
	if (ac == 2)
	{
		master.m_pressed = 0;
		master.yrot = 583;
		master.xrot = 0;
		master.wsize = 1000;
		master.xlen = 0;
		master.ylen = 0;
		master.yiter = 0;
		master.xiter = 0;
		master.scale = 1;
		master.coords = points(av[1], &master); //added pointer
		master.mlx = mlx_init();
		master.win = mlx_new_window(master.mlx, master.wsize, master.wsize, av[1]);
		rotate_key(&master);
		scale(&master);
		re_draw(&master);
//scale(&master);
		//draw(&master, coords, y, x, y+1, x);
		ft_putchar('\n');
		// printf("x%d, xend %d\n", x, master.wsize / (master.xlen + 1) * master.xlen);
		// printf("y%d, yend%d\n", y, master.wsize / (master.ylen + 1) * master.ylen);
		mlx_hook(master.win, 2, 0, my_key_funct, &master); //much faster //master or master->win as last var
		//mlx_hook(master.win, 4, 0, mouse_press_hook, &master);
		//mlx_hook(master.win, 6, 0, motion_hook, &master);
		//mlx_hook(master.win, 5, 0, mouse_release_hook, &master);
		
		mlx_loop(master.mlx);
	}
	return (0);
}
