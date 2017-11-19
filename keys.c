/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:48:44 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 19:39:00 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotscale(t_master *master)
{
	rotate_key(master);
	scale(master);
	return ;
}

void	apldraw(t_master *master, int iter, char xoy)
{
	applyto(master, iter, xoy);
	re_draw(master);
	return ;
}

/*
**92) //9/right pressed
**89) //7/left pressed
**86) //left/4 pressed
**88) //right/6 pressed
**91) //up/8 pressed
**84) //down/2 pressed
*/

int		my_key_funct2(int keycode, t_master *master)
{
	if (keycode == 92)
	{
		rotate_key(master);
		scale(master);
		master->yrot = master->yrot + 1;
		re_draw(master);
	}
	if (keycode == 89)
	{
		rotate_key(master);
		scale(master);
		master->yrot = master->yrot - 1;
		re_draw(master);
	}
	if (keycode == 86)
		apldraw(master, -10, 'x');
	if (keycode == 88)
		apldraw(master, 10, 'x');
	if (keycode == 91)
		apldraw(master, -10, 'y');
	if (keycode == 84)
		apldraw(master, 10, 'y');
	return (0);
}

/*
**126) //up pressed
**125) //down pressed
**124) //right pressed
**123) //left pressed
*/

int		my_key_funct3(int keycode, t_master *master)
{
	if (keycode == 126)
	{
		rotscale(master);
		master->xrot = master->xrot + 1;
		re_draw(master);
	}
	if (keycode == 125)
	{
		rotscale(master);
		master->xrot = master->xrot - 1;
		re_draw(master);
	}
	if (keycode == 124)
	{
		rotscale(master);
		master->zrot = master->zrot + 1;
		re_draw(master);
	}
	if (keycode == 123)
	{
		rotscale(master);
		master->zrot = master->zrot - 1;
		re_draw(master);
	}
	return (0);
}

/*
**69) //plus pressed
**78) //negative pressed
*/

int		my_key_funct(int keycode, t_master *master)
{
	if (keycode == 53)
		exit(1);
	my_key_funct2(keycode, master);
	my_key_funct3(keycode, master);
	if (keycode == 69)
	{
		master->scale += .01;
		rotate_key(master);
		scale(master);
		re_draw(master);
	}
	if (keycode == 78)
	{
		master->scale -= .01;
		rotate_key(master);
		scale(master);
		re_draw(master);
	}
	return (0);
}
