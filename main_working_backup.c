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


//rotates around the z axis
void	rotate_z(t_master *master, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double x1 = x - (master->xlen / 2);//coords->x;
	double y1 = y - (master->ylen / 2);//coords->y;
 	master->coords[y][x].x = ((x1 + 1) * cos(ang)) - ((y1 + 1) * sin(ang));
 	master->coords[y][x].y = ((x1 + 1) * sin(ang)) + ((y1 + 1) * cos(ang));
	master->coords[y][x].x += (master->xlen / 2);
	master->coords[y][x].y += (master->ylen / 2);
	return ;

}
//around y axis
void	rotate_y(t_master *master, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double x1 = x - (master->xlen / 2);//coords->x;
	//double x1 = coords->x;
	double z1 = master->coords[y][x].z;
 	master->coords[y][x].x = ((x1 + 1) * cos(ang)) + ((z1 + 1) * sin(ang));
 	master->coords[y][x].z = (((x1 + 1) * -sin(ang)) + ((z1 + 1) * cos(ang)));
	master->coords[y][x].x += (master->xlen / 2);
	//master->coords[y][x].y += (master->ylen / 2);
	return ;

}
//around x axis
void	rotate_x(t_master *master, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double z1 = master->coords[y][x].z; //////////
	double y1 = y - (master->ylen / 2);//coords->y;
 	master->coords[y][x].y = ((y1 + 1) * cos(ang)) - ((z1 + 1) * sin(ang));
 	master->coords[y][x].z = ((y1 + 1) * sin(ang)) + ((z1 + 1) * cos(ang));
	master->coords[y][x].y += (master->ylen / 2);
	return ;

}

void rotate_key(t_master *master)
{
	int y;
	int x;
	y = 0;
	while(y < master->ylen)
	{
		x = 0;
		while (x < (master->xlen))
		{
			master->coords[y][x].z = master->coords[y][x].rz;
			rotate_y(master, master->yrot, x, y); //replace with master->yrot
			rotate_z(master, master->zrot, x, y);
			rotate_x(master, master->xrot, x, y);
			x++;
		}
		y++;
	}
	return ;
}

void	scale(t_master *master)
{
	int x;
	int y;
	double xscale;
	double yscale;

	y = 0;

	while(y < master->ylen)
	{
		x = 0;
		while (x < (master->xlen))
		{
			xscale = ((master->coords[y][x].x) * (master->wsize / (master->xlen + 1))/2) * (master->scale * master->scale);
			yscale = ((master->coords[y][x].y) * (master->wsize / (master->ylen + 1))/2) * (master->scale * master->scale);
			master->coords[y][x].x = xscale + (master->wsize/4) + (master->xiter); //somwhere in here
			master->coords[y][x].y = yscale + (master->wsize/4) + (master->yiter);
			master->coords[y][x].z = master->coords[y][x].z*(master->wsize/100); //*10 at 1000
			x++;
		}
		y++;
	}
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

void applyto(t_master *master, double iter, char yox)
{
	int y;
	int x;

	y = 0;
	if (yox == 'y')
		master->yiter += iter;
	if (yox == 'x')
		master->xiter += iter;
	while(y < master->ylen)
	{
		x = 0;
		while (x < master->xlen)
		{
			if (yox == 'y')
				master->coords[y][x].y += iter;
			if (yox == 'x')
				master->coords[y][x].x += iter;
			x++;
		}
		y++;
	}
}

int	my_key_funct(int keycode, t_master *master)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 92) //9/right pressed
	{
		rotate_key(master);
		scale(master);
		master->yrot=master->yrot+1;
		re_draw(master);
	}
		
	if (keycode == 89) //7/left pressed
	{
		rotate_key(master);
		scale(master);
		master->yrot=master->yrot -1;
		re_draw(master);
	}
	if (keycode == 126) //up pressed
	{
		rotate_key(master);
		scale(master);
		master->xrot=master->xrot+1;
		re_draw(master);
	}
	if (keycode == 125) //down pressed
	{
		rotate_key(master);
		scale(master);
		master->xrot=master->xrot -1;
		re_draw(master);
	}
	if (keycode == 124) //right pressed
	{
		rotate_key(master);
		scale(master);
		master->zrot=master->zrot+1;
		re_draw(master);
	}
	if (keycode == 123) //left pressed
	{
		rotate_key(master);
		scale(master);
		master->zrot=master->zrot -1;
		re_draw(master);
	}
	if (keycode == 69) //plus pressed
	{
		master->scale += .01;
		rotate_key(master);
		scale(master);
		re_draw(master);
	}
	if (keycode == 78) //negative pressed
	{
		master->scale -= .01;
		rotate_key(master);
		scale(master);
		re_draw(master);
	}
	if (keycode == 86) //left/4 pressed
	{
		applyto(master, -10, 'x');
		re_draw(master);
	}
	if (keycode == 88) //right/6 pressed
	{
		applyto(master, 10, 'x');
		re_draw(master);
	}
	if (keycode == 91) //up/8 pressed
	{
		applyto(master, -10, 'y');
		re_draw(master);
	}
	if (keycode == 84) //down/2 pressed
	{
		applyto(master, 10, 'y');
		re_draw(master);
	}
	return (0);
}

int	motion_hook(int keycode, t_master *master)
{
	//printf("Key event %d\n", keycode);

	//mlx_loop(master->mlx);
	return (0);
}

// int	mouse_press_hook(int keycode, t_master *master)
// {
// 	printf("Key event %d\n", keycode);
// 	if (keycode == 1)
// 		mlx_hook(master->win, 6, 0, motion_hook, master);
// 	return (0);
// }

// int	mouse_press_hook(int keycode, t_master *master)
// {
// 	printf("Key event %d\n", keycode);
// 	if (keycode == 1)
// 		master->m_pressed = 1;
// 	return (0);
// }

// int	mouse_release_hook(int keycode, t_master *master)
// {
// 	//printf("Key event %d\n", keycode);
// 	if (keycode == 1)
// 		master->m_pressed = 0;
// 	return (0);
// }

int main(int ac, char **av)
{
	t_points **coords;
	t_master master;
	int x;
	int y;
	
	if (ac == 2)
	{
		master.m_pressed = 0;
		master.yrot = 583;
		master.xrot = 0;
		master.wsize = 1000;
		master.xlen = 0;
		master.ylen = 0;
		master.yiter = 0;
		master.xiter = 0;
		master.scale = 1;
		master.coords = points(av[1], &master); //added pointer
		master.mlx = mlx_init();
		master.win = mlx_new_window(master.mlx, master.wsize, master.wsize, av[1]);
		rotate_key(&master);
		scale(&master);
		re_draw(&master);
//scale(&master);
		//draw(&master, coords, y, x, y+1, x);
		ft_putchar('\n');
		// printf("x%d, xend %d\n", x, master.wsize / (master.xlen + 1) * master.xlen);
		// printf("y%d, yend%d\n", y, master.wsize / (master.ylen + 1) * master.ylen);
		mlx_hook(master.win, 2, 0, my_key_funct, &master); //much faster //master or master->win as last var
		//mlx_hook(master.win, 4, 0, mouse_press_hook, &master);
		//mlx_hook(master.win, 6, 0, motion_hook, &master);
		//mlx_hook(master.win, 5, 0, mouse_release_hook, &master);
		
		mlx_loop(master.mlx);
	}
	return (0);
}
