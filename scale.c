/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:51:03 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 13:51:29 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_master *master)
{
	int x;
	int y;
	double xscale;
	double yscale;

	y = 0;

	while(y < master->ylen)
	{
		x = 0;
		while (x < (master->xlen))
		{
			xscale = ((master->coords[y][x].x) * (master->wsize / (master->xlen + 1))/2) * (master->scale * master->scale);
			yscale = ((master->coords[y][x].y) * (master->wsize / (master->ylen + 1))/2) * (master->scale * master->scale);
			master->coords[y][x].x = xscale + (master->wsize/4) + (master->xiter); //somwhere in here
			master->coords[y][x].y = yscale + (master->wsize/4) + (master->yiter);
			master->coords[y][x].z = master->coords[y][x].z*(master->wsize/100); //*10 at 1000
			x++;
		}
		y++;
	}
}

void applyto(t_master *master, double iter, char yox)
{
	int y;
	int x;

	y = 0;
	if (yox == 'y')
		master->yiter += iter;
	if (yox == 'x')
		master->xiter += iter;
	while(y < master->ylen)
	{
		x = 0;
		while (x < master->xlen)
		{
			if (yox == 'y')
				master->coords[y][x].y += iter;
			if (yox == 'x')
				master->coords[y][x].x += iter;
			x++;
		}
		y++;
	}
}
