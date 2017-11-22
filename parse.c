/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:52:24 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 22:50:02 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			*znc(t_points **c, char **arr, int *len, int y)
{
	int		x;
	char	**tmp;

	x = -1;
	while (arr[++x])
	{
		c[y][x].x = x;
		c[y][x].y = y;
		if (ft_strchr(arr[x], ','))
		{
			tmp = ft_strsplit(arr[x], ',');
			c[y][x].z = (double)ft_atoi(tmp[0]);
			c[y][x].c = ft_atoi_base(ft_strsub(tmp[1],
							2, ft_strlen(tmp[1])), 16);
			free_array(tmp);
		}
		else
		{
			c[y][x].z = (double)ft_atoi(arr[x]);
			c[y][x].c = c[y][x].z * 6 + ft_atoi_base("000FFFFF", 16) - 256;
		}
		EXIT((c[y][x].z >= 2147483647 || c[y][x].z <= -2147483648));
		c[y][x].rz = c[y][x].z;
	}
	return (0);
}

void		find_hight(t_master *mast, char *filename)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	EXIT((fd = open(filename, O_RDONLY)) == -1);
	while ((ret = get_next_line(fd, &line)))
	{
		EXIT(ret == -1);
		(mast->ylen)++;
	}
	close(fd);
}

t_points	**points(char *filename, t_master *mast)
{
	int			fd;
	char		*line;
	t_points	**twodstruct;

	find_hight(mast, filename);
	twodstruct = (t_points**)malloc(sizeof(t_points*) * mast->ylen);
	mast->j = 1;
	line = NULL;
	EXIT((fd = open(filename, O_RDONLY)) == -1);
	get_next_line(fd, &line);
	mast->xlen = ft_cntdelim(line, ' ');
	EXIT(mast->xlen < 2 && mast->ylen <= 1);
	twodstruct[0] = (t_points*)ft_memalloc(sizeof(t_points) * mast->xlen);
	znc((t_points**)twodstruct, ft_strsplit(line, ' '), &mast->xlen, 0);
	while ((get_next_line(fd, &line)))
	{
		EXIT((ft_cntdelim(line, ' ') > mast->xlen + 1)
			|| (ft_cntdelim(line, ' ') < mast->xlen - 1));
		twodstruct[mast->j] = (t_points*)malloc(sizeof(t_points) * mast->xlen);
		znc(twodstruct, ft_strsplit(line, ' '), &mast->xlen, mast->j);
		mast->j++;
	}
	close(fd);
	free(line);
	return (twodstruct);
}
