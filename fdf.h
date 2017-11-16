/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/15 23:33:16 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct		s_points
{
	double				x;
	double				y;
	double				z;
	char			*c; //supposed to be int
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
	t_points		**coords; //possibly keep everything in here from coords
	int				wsize;
	struct s_master	*next;
}					t_master;



//int		get_next_line(const int fd, char **line);

#endif
