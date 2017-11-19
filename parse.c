/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:52:24 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 18:04:28 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*znc(t_points **stmp, char **arr, int *len, int y)
{
	int x;
	char **tmp;

	x = 0;
	stmp[y][x].c = 1;
	while (arr[x])
	{
		stmp[y][x].x = x;
		stmp[y][x].y = y;

		if (ft_strchr(arr[x], ','))
		{
			tmp = ft_strsplit(arr[x], ',');
			stmp[y][x].z = (double)ft_atoi(tmp[0]);
			stmp[y][x].c = ft_atoi_base(ft_strsub(tmp[1], 2, ft_strlen(tmp[1])), 16); //ft_atoi(tmp[1]); //or just the string
			free(tmp);
		}
		else
		{
			stmp[y][x].z = (double)ft_atoi(arr[x]);
			stmp[y][x].c = stmp[y][x].z * 6 + ft_atoi_base("000FFFFF", 16) - 256;
		}
		stmp[y][x].rz = stmp[y][x].z;
		x++;
	}
	return (0);
}

t_points **points(char *filename, t_master *master){
	int		fd;
	char	*line;
	int		y;
	t_points **twodstruct; //fix to find the right val
	t_points **cpy;
	int lentmp = 0;
	int *xlen;
	char *tmp;

//all this is to figut out the height of the file
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
		(master->ylen)++;
	close(fd);
	twodstruct = (t_points**)malloc(sizeof(t_points*) * master->ylen);
//////////////////

	y = 1; //y use the tmp var for the first one at index 0
	line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, &line); //check to see if gnl runs
	tmp = line;
	master->xlen = ft_cntdelim(tmp, ' ');// + 1;
	twodstruct[0] = (t_points*)ft_memalloc(sizeof(t_points) * master->xlen);
	znc((t_points**)twodstruct, ft_strsplit(line, ' '), &master->xlen, 0);
	while ((get_next_line(fd, &line)))
	{
		twodstruct[y] = (t_points*)malloc(sizeof(t_points) * master->xlen);
		znc((t_points**)twodstruct, ft_strsplit(line, ' '), &master->xlen, y);
		y++;
	}
	//free(twodstruct);
	close(fd);
	free(line);
	return ((t_points**)twodstruct);
}