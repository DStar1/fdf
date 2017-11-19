/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:48:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 19:10:56 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotscale(t_master *master)
{
	rotate_key(master);
	scale(master);
	return ;
}

int	my_key_funct(int keycode, t_master *master)
{
	if (keycode == 53)
		exit(1);
	// if (keycode == 92) //9/right pressed
	// {
	// 	rotate_key(master);
	// 	scale(master);
	// 	master->yrot=master->yrot+1;
	// 	re_draw(master);
	// }
		
	// if (keycode == 89) //7/left pressed
	// {
	// 	rotate_key(master);
	// 	scale(master);
	// 	master->yrot=master->yrot -1;
	// 	re_draw(master);
	// }
	if (keycode == 126) //up pressed
	{
		rotscale(&master);
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

int	my_key_funct2(int keycode, t_master *master)
{
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
	return (0);
}