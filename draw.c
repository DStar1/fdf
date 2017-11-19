/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:46:31 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 13:47:47 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw(t_master *master, int y11, int x11, int y22, int x22)
{
////////////////////writes line to the screen//////////////////
	double x1 = master->coords[y11][x11].x;
	double y1 = master->coords[y11][x11].y;
	double x2 = master->coords[y22][x22].x;
	double y2 = master->coords[y22][x22].y;
	// int x1 = 70;
	// int y1 = 90;
	// int x2 = 70;
	// int y2 = 0;
	
	int numerator;
	int longest;
	int shortest;
	int i;
	int w;
	int h;
	i = 0;
	w = x2 - x1;
    h = y2 - y1;
    double dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
    if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1;
    if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1;
    if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1;
    longest = abs(w) ; //possibly create ft_abs function
    shortest = abs(h) ;
    if (!(longest>shortest))
	{
        longest = abs(h);
        shortest = abs(w);
        if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1;
        dx2 = 0 ;
    }
    numerator = longest >> 1;
    while (i<=longest)
	{
        mlx_pixel_put(master->mlx, master->win, x1, y1, master->coords[y11][x11].c);//0x000FFFFF);
        numerator += shortest;
        if (!(numerator<longest))
		{
            numerator -= longest;
            x1 += dx1;
            y1 += dy1;
        }
		else {
            x1 += dx2;
            y1 += dy2;
        }
		i++;
    }
	return ;
}

void	re_draw(t_master *master)
{
	int y;
	int x;
	y = 0;

	mlx_clear_window(master->mlx, master->win);
	y = 0;
	while(y < master->ylen)
	{
		x = 0;
		while (x < master->xlen)
		{
			if (x < (master->xlen)-1)
				draw(master, y, x, y, x + 1);
			if (y < (master->ylen)-1)
				draw(master, y, x, y + 1, x);
			x++;
		}
		y++;
	}
	return ;
}
