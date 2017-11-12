/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:15:38 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/11 19:05:07 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct		s_master
{
	void			*mlx;
	void			*win;
	int				ylen;
	int				xlen;
	int				wsize;
	struct s_master	*next;
}					t_master;

typedef struct		s_points
{
	int				x;
	int				y;
	int				z;
	char			*c; //supposed to be int
	void			*content;
	struct s_points	*next;
}					t_points;

//int		get_next_line(const int fd, char **line);

#endif
