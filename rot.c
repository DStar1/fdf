/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:20:10 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 13:23:09 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//rotates around the z axis
void	rotate_z(t_master *master, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double x1 = x - (master->xlen / 2);//coords->x;
	double y1 = y - (master->ylen / 2);//coords->y;
 	master->coords[y][x].x = ((x1 + 1) * cos(ang)) - ((y1 + 1) * sin(ang));
 	master->coords[y][x].y = ((x1 + 1) * sin(ang)) + ((y1 + 1) * cos(ang));
	master->coords[y][x].x += (master->xlen / 2);
	master->coords[y][x].y += (master->ylen / 2);
	return ;

}
//around y axis
void	rotate_y(t_master *master, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double x1 = x - (master->xlen / 2);//coords->x;
	//double x1 = coords->x;
	double z1 = master->coords[y][x].z;
 	master->coords[y][x].x = ((x1 + 1) * cos(ang)) + ((z1 + 1) * sin(ang));
 	master->coords[y][x].z = (((x1 + 1) * -sin(ang)) + ((z1 + 1) * cos(ang)));
	master->coords[y][x].x += (master->xlen / 2);
	//master->coords[y][x].y += (master->ylen / 2);
	return ;

}
//around x axis
void	rotate_x(t_master *master, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double z1 = master->coords[y][x].z; //////////
	double y1 = y - (master->ylen / 2);//coords->y;
 	master->coords[y][x].y = ((y1 + 1) * cos(ang)) - ((z1 + 1) * sin(ang));
 	master->coords[y][x].z = ((y1 + 1) * sin(ang)) + ((z1 + 1) * cos(ang));
	master->coords[y][x].y += (master->ylen / 2);
	return ;

}

void rotate_key(t_master *master)
{
	int y;
	int x;
	y = 0;
	while(y < master->ylen)
	{
		x = 0;
		while (x < (master->xlen))
		{
			master->coords[y][x].z = master->coords[y][x].rz;
			rotate_y(master, master->yrot, x, y); //replace with master->yrot
			rotate_z(master, master->zrot, x, y);
			rotate_x(master, master->xrot, x, y);
			x++;
		}
		y++;
	}
	return ;
}
