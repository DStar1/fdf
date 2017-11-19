/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 18:03:32 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//# define Z 10

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct		s_points
{
	double				x;
	double				y;
	double				z;
	double				rz;
	int				c; //supposed to be int
	void			*content;
	struct s_points	*next;
}					t_points;

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
	int				m_pressed;
	t_points		**coords; //possibly keep everything in here from coords
	int				wsize;
	struct s_master	*next;
}					t_master;

void rotate_key(t_master *master);
t_points **points(char *filename, t_master *master);
void	scale(t_master *master);
void applyto(t_master *master, double iter, char yox);
int	my_key_funct(int keycode, t_master *master);
void	re_draw(t_master *master);

#endif
