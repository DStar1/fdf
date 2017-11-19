/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:20:10 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 18:34:17 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_master *master, double ang, int x, int y)
{
	double x1;
	double y1;

	ang = ang * (M_PI / 180);
	x1 = x - (master->xlen / 2);
	y1 = y - (master->ylen / 2);
	master->coords[y][x].x = ((x1 + 1) * cos(ang)) - ((y1 + 1) * sin(ang));
	master->coords[y][x].y = ((x1 + 1) * sin(ang)) + ((y1 + 1) * cos(ang));
	master->coords[y][x].x += (master->xlen / 2);
	master->coords[y][x].y += (master->ylen / 2);
	return ;
}

void	rotate_y(t_master *master, double ang, int x, int y)
{
	double x1;
	double z1;

	ang = ang * (M_PI / 180);
	x1 = x - (master->xlen / 2);
	z1 = master->coords[y][x].z;
	master->coords[y][x].x = ((x1 + 1) * cos(ang)) + ((z1 + 1) * sin(ang));
	master->coords[y][x].z = (((x1 + 1) * -sin(ang)) + ((z1 + 1) * cos(ang)));
	master->coords[y][x].x += (master->xlen / 2);
	return ;
}

void	rotate_x(t_master *master, double ang, int x, int y)
{
	double z1;
	double y1;

	ang = ang * (M_PI / 180);
	z1 = master->coords[y][x].z;
	y1 = y - (master->ylen / 2);
	master->coords[y][x].y = ((y1 + 1) * cos(ang)) - ((z1 + 1) * sin(ang));
	master->coords[y][x].z = ((y1 + 1) * sin(ang)) + ((z1 + 1) * cos(ang));
	master->coords[y][x].y += (master->ylen / 2);
	return ;
}

void	rotate_key(t_master *master)
{
	int y;
	int x;

	y = 0;
	while (y < master->ylen)
	{
		x = 0;
		while (x < (master->xlen))
		{
			master->coords[y][x].z = master->coords[y][x].rz;
			rotate_y(master, master->yrot, x, y);
			rotate_z(master, master->zrot, x, y);
			rotate_x(master, master->xrot, x, y);
			x++;
		}
		y++;
	}
	return ;
}
