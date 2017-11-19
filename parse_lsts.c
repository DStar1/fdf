/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:52:24 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 18:01:08 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*znc(t_points **coords, char **arr, int *len, int y)
{
	int x;
	char **tmp;
	//char tmp2[2];
    //int fre;

	x = 0;
	coords[y][x].c = 1;
    //fre = 0;
	//printf("%d\n", ft_atoi_base("000FFFFF", 16));
	while (arr[x])
	{
		coords[y][x].x = x;
		coords[y][x].y = y;
		if (ft_strchr(arr[x], ','))
		{
			tmp = ft_strsplit(arr[x], ',');
			//tmp2 = *tmp[0];
            ft_putarr(tmp);
			coords[y][x].z = (double)ft_atoi(tmp[0]);
			coords[y][x].c = 0xFF0000;//ft_atoi_base(ft_strsub(tmp[1], 2, ft_strlen(tmp[1])), 16); //ft_atoi(tmp[1]); //or just the string //this is a leak!!!!!!!!!!!!!!!!
			free_array(tmp);
            //fre = 1;
            //free(tmp);
		}
		else
		{
			coords[y][x].z = (double)ft_atoi(arr[x]);
			coords[y][x].c = coords[y][x].z * 6 + ft_atoi_base("000FFFFF", 16) - 256;
		}
		coords[y][x].rz = coords[y][x].z;
		x++;
	}
    // if (fre == 1)
    //     free(tmp); //added for leaks
    free_array(arr);
    //free(arr);
	return (0);
}

t_list *reading(t_points ***coords, t_master *master, char *filename, t_list **length)
{
	int		fd;
	char	*line;
	// t_list *length;
	t_list *begin;
	char *tmp;

	begin = length;
	master->ylen = 0;
//all this is to figut out the height of the file
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
						// printf("%d\n", (int)master->ylen);
						// printf("%s\n", line);
		length = ft_lstnew(line, ft_strlen(line));
		printf("%s\n", length->content);
		length = length->next;
		(master->ylen)++;
	}
	length = ft_lstnew(NULL, 0);
	close(fd);
	free(line);
	// coords = (t_points**)malloc(sizeof(t_points*) * master->ylen);
//////////////////
	return (begin);
}

t_points **points(char *filename, t_master *master)
{
	int		y;
	t_points **coords; //fix to find the right val
	//t_points **cpy;
	int lentmp = 0;
	int *xlen;
	t_list *length;
	//char *tmp;

// //all this is to figut out the height of the file
// 	if ((fd = open(filename, O_RDONLY)) == -1)
// 		return (0);
// 	while (get_next_line(fd, &line))
// 		(master->ylen)++;
// 	close(fd);
// 	coords = (t_points**)malloc(sizeof(t_points*) * master->ylen);
// //////////////////

	////free(line);
	// y = 1; //y use the tmp var for the first one at index 0
	// line = NULL;
	// if ((fd = open(filename, O_RDONLY)) == -1)
	// 	return (0);
	// get_next_line(fd, &line); //check to see if gnl runs
	// //tmp = line; //no
	// master->xlen = ft_cntdelim(line, ' ');// + 1;
	// coords[0] = (t_points*)ft_memalloc(sizeof(t_points) * master->xlen);
	// znc(coords, ft_strsplit(line, ' '), &master->xlen, 0);
    // free(line); //no
	// while ((get_next_line(fd, &line)))
	// {
	// 	if (ft_cntdelim(line, ' ') != master->xlen) ///checks to see if all lines have the same amount of points
	// 	{
	// 		ft_putstr("INVALID FILE! EXITING NOW :(");
	// 		exit (1);
	// 	}
    //     coords[y] = (t_points*)malloc(sizeof(t_points) * master->xlen);
	// 	znc(coords, ft_strsplit(line, ' '), &master->xlen, y);
	// 	y++;
	// }
//printf("in points: %s\n", length->content);
	reading(&coords, master, filename, &length);
	printf("in points: %s\n", length->content);
	coords = (t_points**)malloc(sizeof(t_points*) * master->ylen);
	while (y < master->ylen)
	{
		if (y == 0)
			master->xlen = ft_cntdelim(length->content, ' ');
		if (!length || ft_cntdelim(length->content, ' ') != master->xlen) ///checks to see if all lines have the same amount of points
		{
			ft_putstr("INVALID FILE! EXITING NOW :(");
			exit (1);
		}
		coords[y] = (t_points*)ft_memalloc(sizeof(t_points) * master->xlen);
		znc(coords, ft_strsplit(length->content, ' '), &master->xlen, y);
		length = length->next;
		y++;
	}

	//close(fd);
	//free(line);
    //free(tmp); //no
	return (coords);
}
//printf("%d\n", (int)master->xlen);