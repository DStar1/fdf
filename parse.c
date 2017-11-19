/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:52:24 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 19:00:12 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			*znc(t_points **c, char **arr, int *len, int y)
{
	int		x;
	char	**tmp;

	x = 0;
	while (arr[x])
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
		c[y][x].rz = c[y][x].z;
		x++;
	}
	return (0);
}

// void		gnlcheck(int fd, char **line, t_master *master, t_points ***twodstruct)
// {
// 	int y;

// 	y = 1;
// 	while ((get_next_line(fd, line)))
// 	{
// 		*twodstruct[y] = (t_points*)malloc(sizeof(t_points) * master->xlen);
// 		znc(*twodstruct, ft_strsplit(*line, ' '), &master->xlen, y);
// 		y++;
// 	}
// 	return ;
// }

t_points	**points(char *filename, t_master *master)
{
	int			fd;
	char		*line;
	int			y;
	t_points	**twodstruct;

	RETURN(0, ((fd = open(filename, O_RDONLY)) == -1));
	while (get_next_line(fd, &line))
		(master->ylen)++;
	close(fd);
	twodstruct = (t_points**)malloc(sizeof(t_points*) * master->ylen);
	y = 1;
	line = NULL;
	RETURN(0, ((fd = open(filename, O_RDONLY)) == -1));
	get_next_line(fd, &line);
	master->xlen = ft_cntdelim(line, ' ');
	twodstruct[0] = (t_points*)ft_memalloc(sizeof(t_points) * master->xlen);
	znc((t_points**)twodstruct, ft_strsplit(line, ' '), &master->xlen, 0);
	//gnlcheck(fd, &line, master, &twodstruct);
	while ((get_next_line(fd, &line)))
	{
		twodstruct[y] = (t_points*)malloc(sizeof(t_points) * master->xlen);
		znc((t_points**)twodstruct, ft_strsplit(line, ' '), &master->xlen, y);
		y++;
	}
	close(fd);
	free(line);
	return ((t_points**)twodstruct);
}
