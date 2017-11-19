/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:51:03 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 21:02:26 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale(t_master *m)
{
	int		x;
	int		y;
	double	xscale;
	double	yscale;

	y = 0;
	while (y < m->ylen)
	{
		x = 0;
		while (x < (m->xlen))
		{
			xscale = ((m->coords[y][x].x) * (m->wsize / (m->xlen + 1)) / 2)
						* (m->scale * m->scale);
			yscale = ((m->coords[y][x].y) * (m->wsize / (m->ylen + 1)) / 2)
						* (m->scale * m->scale);
			m->coords[y][x].x = xscale + (m->wsize / 4) + (m->xiter);
			m->coords[y][x].y = yscale + (m->wsize / 4) + (m->yiter);
			m->coords[y][x].z = m->coords[y][x].z * (m->wsize / 100);
			x++;
		}
		y++;
	}
}

void	applyto(t_master *m, double iter, char yox)
{
	int y;
	int x;

	y = 0;
	if (yox == 'y')
		m->yiter += iter;
	if (yox == 'x')
		m->xiter += iter;
	while (y < m->ylen)
	{
		x = 0;
		while (x < m->xlen)
		{
			if (yox == 'y')
				m->coords[y][x].y += iter;
			if (yox == 'x')
				m->coords[y][x].x += iter;
			x++;
		}
		y++;
	}
}
