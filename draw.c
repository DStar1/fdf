/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:46:31 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 20:56:24 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	allvs(t_master *master, t_vars *v)
{
	v->x1 = master->coords[master->y11][master->x11].x;
	v->y1 = master->coords[master->y11][master->x11].y;
	v->x2 = master->coords[master->y22][master->x22].x;
	v->y2 = master->coords[master->y22][master->x22].y;
	v->c = master->coords[master->y22][master->x22].c;
	v->i = 0;
	v->w = v->x2 - v->x1;
	v->h = v->y2 - v->y1;
	v->dx1 = 0;
	v->dy1 = 0;
	v->dx2 = 0;
	v->dy2 = 0;
	return ;
}

void	checkif(t_vars *v)
{
	if (v->w < 0)
		v->dx1 = -1;
	else if (v->w > 0)
		v->dx1 = 1;
	if (v->h < 0)
		v->dy1 = -1;
	else if (v->h > 0)
		v->dy1 = 1;
	if (v->w < 0)
		v->dx2 = -1;
	else if (v->w > 0)
		v->dx2 = 1;
	v->longest = abs(v->w);
	v->shortest = abs(v->h);
	if (!(v->longest > v->shortest))
	{
		v->longest = abs(v->h);
		v->shortest = abs(v->w);
		if (v->h < 0)
			v->dy2 = -1;
		else if (v->h > 0)
			v->dy2 = 1;
		v->dx2 = 0;
	}
	return ;
}

void	draw(t_master *master, t_vars *v)
{
	allvs(master, v);
	checkif(v);
	v->numerator = v->longest >> 1;
	while (v->i <= v->longest)
	{
		mlx_pixel_put(master->mlx, master->win, v->x1, v->y1, v->c);
		v->numerator += v->shortest;
		if (!(v->numerator < v->longest))
		{
			v->numerator -= v->longest;
			v->x1 += v->dx1;
			v->y1 += v->dy1;
		}
		else
		{
			v->x1 += v->dx2;
			v->y1 += v->dy2;
		}
		v->i++;
	}
	return ;
}

void	xandy(t_master *master, int y11, int x11, char yox)
{
	master->x11 = x11;
	master->y11 = y11;
	if (yox == 'x')
	{
		master->x22 = x11 + 1;
		master->y22 = y11;
	}
	else if (yox == 'y')
	{
		master->x22 = x11;
		master->y22 = y11 + 1;
	}
	return ;
}

void	re_draw(t_master *master)
{
	int		y;
	int		x;
	t_vars	v;

	mlx_clear_window(master->mlx, master->win);
	y = 0;
	while (y < master->ylen)
	{
		x = 0;
		while (x < master->xlen)
		{
			if (x < (master->xlen) - 1)
			{
				xandy(master, y, x, 'x');
				draw(master, &v);
			}
			if (y < (master->ylen) - 1)
			{
				xandy(master, y, x, 'y');
				draw(master, &v);
			}
			x++;
		}
		y++;
	}
}
