/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:48:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 13:49:22 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	my_key_funct(int keycode, t_master *master)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 92) //9/right pressed
	{
		rotate_key(master);
		scale(master);
		master->yrot=master->yrot+1;
		re_draw(master);
	}
		
	if (keycode == 89) //7/left pressed
	{
		rotate_key(master);
		scale(master);
		master->yrot=master->yrot -1;
		re_draw(master);
	}
	if (keycode == 126) //up pressed
	{
		rotate_key(master);
		scale(master);
		master->xrot=master->xrot+1;
		re_draw(master);
	}
	if (keycode == 125) //down pressed
	{
		rotate_key(master);
		scale(master);
		master->xrot=master->xrot -1;
		re_draw(master);
	}
	if (keycode == 124) //right pressed
	{
		rotate_key(master);
		scale(master);
		master->zrot=master->zrot+1;
		re_draw(master);
	}
	if (keycode == 123) //left pressed
	{
		rotate_key(master);
		scale(master);
		master->zrot=master->zrot -1;
		re_draw(master);
	}
	if (keycode == 69) //plus pressed
	{
		master->scale += .01;
		rotate_key(master);
		scale(master);
		re_draw(master);
	}
	if (keycode == 78) //negative pressed
	{
		master->scale -= .01;
		rotate_key(master);
		scale(master);
		re_draw(master);
	}
	if (keycode == 86) //left/4 pressed
	{
		applyto(master, -10, 'x');
		re_draw(master);
	}
	if (keycode == 88) //right/6 pressed
	{
		applyto(master, 10, 'x');
		re_draw(master);
	}
	if (keycode == 91) //up/8 pressed
	{
		applyto(master, -10, 'y');
		re_draw(master);
	}
	if (keycode == 84) //down/2 pressed
	{
		applyto(master, 10, 'y');
		re_draw(master);
	}
	return (0);
}

int	motion_hook(int keycode, t_master *master)
{
	//printf("Key event %d\n", keycode);

	//mlx_loop(master->mlx);
	return (0);
}

// int	mouse_press_hook(int keycode, t_master *master)
// {
// 	printf("Key event %d\n", keycode);
// 	if (keycode == 1)
// 		mlx_hook(master->win, 6, 0, motion_hook, master);
// 	return (0);
// }

// int	mouse_press_hook(int keycode, t_master *master)
// {
// 	printf("Key event %d\n", keycode);
// 	if (keycode == 1)
// 		master->m_pressed = 1;
// 	return (0);
// }

// int	mouse_release_hook(int keycode, t_master *master)
// {
// 	//printf("Key event %d\n", keycode);
// 	if (keycode == 1)
// 		master->m_pressed = 0;
// 	return (0);
// }