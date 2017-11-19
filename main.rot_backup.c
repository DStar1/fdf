#include "fdf.h"



int		*znc(t_points **stmp, char **arr, int *len, int y)
{
	int x;
	char **tmp;

	x = 0;
	while (arr[x])
	{
		stmp[y][x].x = x;
		stmp[y][x].y = y;
		if (ft_strchr(arr[x], ';'))
		{
			tmp = ft_strsplit(arr[x], ';');
			stmp[y][x].z = (double)ft_atoi(tmp[0]);
			stmp[y][x].c = tmp[1]; //ft_atoi(tmp[1]); //or just the string
			free(tmp);
		}
		else
			stmp[y][x].z = (double)ft_atoi(arr[x]);
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



	printf("XLEN=%d, YLEN=%d, %s\n", master->xlen, master->ylen, tmp);



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
	//char z = master->coords[y11][x11].z;
	//printf("p1(%d, %d) p2(%d, %d)\n\n", (int)y1, (int)x1, (int)y2, (int)x2);

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
		// if (z)
		// 	mlx_pixel_put(master->mlx, master->win, x1, y1, 0x00000FFF); //add color here if z
		// else
        	mlx_pixel_put(master->mlx, master->win, x1, y1, 0x000FFFFF);
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
void	rotate_z(t_points *coords, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double x1 = x;//coords->x;
	double y1 = y;//coords->y;
 	coords->x = ((x1 + 1) * cos(ang)) - ((y1 + 1) * sin(ang));
 	coords->y = ((x1 + 1) * sin(ang)) + ((y1 + 1) * cos(ang));
	return ;

} //http://graphics.cs.cmu.edu/nsp/course/15-462/Spring04/slides/04-transform.pdf
//around y axis
void	rotate_y(t_points *coords, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double x1 = x;//coords->x;
	//double x1 = coords->x;
	double z1 = coords->z;
 	coords->x = ((x1 + 1) * cos(ang)) + ((z1 + 1) * sin(ang));
 	coords->z = (((x1 + 1) * -sin(ang)) + ((z1 + 1) * cos(ang)));
	return ;

}
//around x axis
void	rotate_x(t_points *coords, double ang, int x, int y)
{
	ang = ang * (M_PI/180);
	double z1 = coords->z; //////////
	double y1 = y;//coords->y;
 	coords->y = ((y1 + 1) * cos(ang)) - ((z1 + 1) * sin(ang));
 	coords->z = ((y1 + 1) * sin(ang)) + ((z1 + 1) * cos(ang));
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

// 			// printf("((%d, %d):", coords[y][x].y, coords[y][x].x);
			master->coords[y][x].z = master->coords[y][x].rz;
			rotate_y(&(master->coords[y][x]), master->yrot, x, y); //replace with master->yrot
			rotate_z(&(master->coords[y][x]), master->zrot, x, y);
			rotate_x(&(master->coords[y][x]), master->xrot, x, y);
			//printf("(x:%d:%d, y:%d:%d, z:%d)\n", x, (int)master->coords[y][x].x, y, (int)master->coords[y][x].y), (int)master->coords[y][x].z;
// 			//printf("(%d, %d))|", (int)coords[y][x].y, (int)coords[y][x].x);
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

	y = 0;
	while(y < master->ylen)
	{
		x = 0;
		while (x < (master->xlen))
		{

			// printf("((%d, %d):", coords[y][x].y, coords[y][x].x);
			//printf("x:%d, y%d: angle: %f,\n", x, y, (x * cos(ang)) - (y * sin(ang)));
			master->coords[y][x].x = ((master->coords[y][x].x) * (master->wsize / (master->xlen + 1))/2+(master->wsize/2));// + (double)master->yiter; //somwhere in here
			master->coords[y][x].y = ((master->coords[y][x].y) * (master->wsize / (master->ylen + 1))/2+(master->wsize/5));// + (double)master->xiter;
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

			// printf("%d, %d\n", master.ylen, master.xlen);
	//		printf("(%d, %d) |\n", coords[1][1].y, coords[1][1].x);
	y = 0;
	while(y < master->ylen)
	{
		x = 0;
		while (x < master->xlen)
		{
			if (x < (master->xlen)-1){
				draw(master, y, x, y, x + 1);
				//printf("x: %d,xlen: %d | p1(%d, %d) p2(%d, %d)\n", x, master->xlen, (int)master->coords[y][x].y, (int)master->coords[y][x].x, (int)master->coords[y][x+1].y, (int)master->coords[y][x+1].x);
				}
			if (y < (master->ylen)-1){
				draw(master, y, x, y + 1, x);
				//printf("y: %d,ylen: %d | p1(%d, %d) p2(%d, %d)\n", y, master->ylen, (int)master->coords[y][x].y, (int)master->coords[y][x].x, (int)master->coords[y+1][x].y, (int)master->coords[y+1][x].x);
				}
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
	while(y < master->ylen)
	{
		x = 0;
		while (x < master->xlen)
		{
			if (yox == 'y')
			{
				//printf("before button: %d\n", (int)master->coords[y][x].y);
				//master->coords[y][x].y = (y+1) * (master->wsize / (master->ylen + 1))/2+500+iter;
				master->coords[y][x].y += iter;
				master->yiter += iter;
				//printf("after button: %d\n", (int)master->coords[y][x].y);
			}
			if (yox == 'x')
			{
				//master->coords[y][x].x = (x+1) * (master->wsize / (master->xlen + 1))/2+500+iter;
				master->coords[y][x].x += iter;
				master->xiter += iter;
			}
			x++;
		}
		y++;
	}
}

//mlx_destroy();

int	my_key_funct(int keycode, t_master *master)
{
	printf("Key event %d\n", keycode);
	// int x = 300;
	// int y = 300;
	if (keycode == 53)
		exit(1);
	if (keycode == 124) //right pressed
	{
		rotate_key(master);
		scale(master);
		master->yrot=master->yrot+1;
		//printf("%d\n", (int)master->yrot);
		re_draw(master);
	}
		
	if (keycode == 123) //left pressed
	{
		rotate_key(master);
		scale(master);
		master->yrot=master->yrot -1;
		//printf("%d\n", (int)master->yrot);
		re_draw(master);
	}
	if (keycode == 126) //up pressed
	{
		rotate_key(master);
		scale(master);
		master->xrot=master->xrot+1;
		//printf("%d\n", (int)master->xrot);
		re_draw(master);
	}
	if (keycode == 125) //down pressed
	{
		rotate_key(master);
		scale(master);
		master->xrot=master->xrot -1;
		//printf("%d\n", (int)master->xrot);
		re_draw(master);
	}


	if (keycode == 92) //9/right pressed
	{
		rotate_key(master);
		scale(master);
		master->zrot=master->zrot+1;
		//printf("%d\n", (int)master->xrot);
		re_draw(master);
	}
	if (keycode == 89) //7/left pressed
	{
		rotate_key(master);
		scale(master);
		master->zrot=master->zrot -1;
		//printf("%d\n", (int)master->xrot);
		re_draw(master);
	}




	if (keycode == 86) //left/4 pressed
	{
		applyto(master, -10, 'x');
		//printf("%d\n", );
		re_draw(master);
	}
	if (keycode == 88) //right/6 pressed
	{
		applyto(master, 10, 'x');
		//printf("%d\n", );
		re_draw(master);
	}
	if (keycode == 91) //up/8 pressed
	{
		applyto(master, -10, 'y');
		//printf("%d\n", );
		re_draw(master);
	}
	if (keycode == 84) //down/2 pressed
	{
		applyto(master, 10, 'y');
		//printf("%d\n", );
		re_draw(master);
	}
	//mlx_pixel_put(master->mlx, master->win, rand()%400, rand()%400, 16711935);//0xFF00FF); //use struct
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
