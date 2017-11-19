/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 20:41:28 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct		s_points
{
	double			x;
	double			y;
	double			z;
	double			rz;
	int				c;
	void			*content;
	struct s_points	*next;
}					t_points;

typedef struct		s_vars
{
	double			x1;
	double			y1;
	double			x2;
	double			y2;
	int				numerator;
	int				longest;
	int				shortest;
	int				i;
	int				w;
	int				h;
	double			dx1;
	double			dy1;
	double			dx2;
	double			dy2;
	int				x11;
	int				y11;
	int				x22;
	int				y22;
	int				c;
	// double			z;
	// double			rz;
	// int				c;
	void			*content;
	struct s_vars	*next;
}					t_vars;

typedef struct		s_master
{
	void			*mlx;
	void			*win;
	int				ylen;
	int				xlen;
	double			yrot;
	double			zrot;
	double			xrot;
	double			yiter;
	double			xiter;
	double			scale;
	int				x11;
	int				y11;
	int				x22;
	int				y22;
	int				m_pressed;
	t_points		**coords;
	int				wsize;
	struct s_master	*next;
}					t_master;

void				rotate_key(t_master *master);
t_points			**points(char *filename, t_master *master);
void				scale(t_master *master);
void				applyto(t_master *master, double iter, char yox);
int					my_key_funct(int keycode, t_master *master);
void				re_draw(t_master *master);

#endif
