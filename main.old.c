#include "fdf.h"

int	my_key_funct(int keycode, t_master *master)
{
	printf("Key event %d\n", keycode);
	// int x = 300;
	// int y = 300;
	if (keycode == 53)
		exit(1);
	// if (keycode == 124) //right pressed
	// 	//coords[y][x].x++;
	// if (keycode == 123) //left pressed
	// 	coords[y][x].x--;
	// if (keycode == 126) //up pressed
	// 	coords[y][x].y++;
	// if (keycode == 125) //down pressed
	// 	coords[y][x].y--;
	//mlx_pixel_put(master->mlx, master->win, rand()%400, rand()%400, 16711935);//0xFF00FF); //use struct
	return (0);
}

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
			stmp[y][x].z = ft_atoi(tmp[0]);
			stmp[y][x].c = tmp[1]; //ft_atoi(tmp[1]); //or just the string
			free(tmp);
		}
		else
			stmp[y][x].z = ft_atoi(arr[x]);
		x++;
	}
	return (0);
}

// void printpoints(int xlen, int ylen, t_points **twodstruct)
// {
// 	int y = 0;
// 	int x = 0;
// 	while (y < ylen)
// 	{
// 		x = 0;
// 		while (x < xlen)
// 		{
// 			//printf("c: %s, z: %d | ", twodstruct[y][x].c, twodstruct[y][x].z); //trying to make a 2d struct array
// 			printf("(%d, %d)z=%d||", twodstruct[y][x].y, twodstruct[y][x].x, twodstruct[y][x].z);
// 			x++;
// 		}
// 		printf("\n");
// 		free(twodstruct[y]);
// 		y++;
// 	}
// 	free(twodstruct);
// }

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
	master->xlen = ft_cntdelim(tmp, ' ');
	twodstruct[0] = (t_points*)ft_memalloc(sizeof(t_points) * master->xlen);
	znc((t_points**)twodstruct, ft_strsplit(line, ' '), &master->xlen, 0);
	while ((get_next_line(fd, &line)))
	{
		twodstruct[y] = (t_points*)malloc(sizeof(t_points) * master->xlen);
		znc((t_points**)twodstruct, ft_strsplit(line, ' '), &master->xlen, y);
		y++;
	}
//	printpoints(master->xlen, master->ylen, twodstruct); //passing the address for freeing
	//free(twodstruct);
	close(fd);
	free(line);
	return ((t_points**)twodstruct);
}

void draw(t_master *master, t_points **coords, int y11, int x11, int y22, int x22)
{
////////////////////writes line to the screen//////////////////
	double x1 = coords[y11][x11].x;
	double y1 = coords[y11][x11].y;
	double x2 = coords[y22][x22].x;
	double y2 = coords[y22][x22].y;

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
        longest = abs(h) ;
        shortest = abs(w) ;
        if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1 ;
        dx2 = 0 ;
    }
    numerator = longest >> 1;
    while (i<=longest)
	{
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


//dont fully understand how to impliment
t_points	rotate(t_points coords, int ang, int x, int y)
{
	//z
	t_points coords1;
	//printf("%d", (int)coords.x);

	ang = ang * (M_PI/180);
 	coords1.x = (x + 1 * cos(ang)) - (y + 1 * sin(ang));
 	coords1.y = (x + 1 * sin(ang)) + (y + 1 * cos(ang));

	//y
	//coords[y][x]->x = coords[y][x]->x * cos(ang) + coords[y][x]->z * sin(ang);
	return (coords1);

} //http://graphics.cs.cmu.edu/nsp/course/15-462/Spring04/slides/04-transform.pdf

// void	rotate(t_points ***coords, int ang, int x, int y)
// {
// 	ang = ang * (M_PI/180);
// 	coords[y][x]->x = (x+1 * cos(ang)) - (y+1 * sin(ang));
// 	coords[y][x]->y = (x+1 * sin(ang)) + (y+1 * cos(ang));
// 	return ;
// }


int main(int ac, char **av)
{
	t_points **coords;
	t_master master;
	int x;
	int y;
	
	if (ac == 2)
	{
		master.wsize = 1000;
		master.xlen = 0;
		master.ylen = 0;
		coords = points(av[1], &master); //added pointer
		master.mlx = mlx_init();
		master.win = mlx_new_window(master.mlx, master.wsize, master.wsize, av[1]);
		//x = 0;
		int ang = 45 * (M_PI/180);
		//ang = 0;
		y = 0;
		while(y < master.ylen)
		{
			x = 0;
			while (x < (master.xlen))
			{

				// printf("((%d, %d):", coords[y][x].y, coords[y][x].x);
				//printf("x:%d, y%d: angle: %f,\n", x, y, (x * cos(ang)) - (y * sin(ang)));
				//coords[y][x] = rotate(coords[y][x], 0, x, y);
				coords[y][x].x = ((coords[y][x].x + 1) * cos(ang)) - ((coords[y][x].y + 1) * sin(ang)); //was just x or y in place of coords[y][x].x/y
 				coords[y][x].y = ((coords[y][x].x + 1) * sin(ang)) + ((coords[y][x].y + 1) * cos(ang));
				
				coords[y][x].x = (coords[y][x].x) * (master.wsize / (master.xlen + 1))/2+500;
				coords[y][x].y = (coords[y][x].y) * (master.wsize / (master.ylen + 1))/2+100;
				//printf("(%d, %d))|", (int)coords[y][x].y, (int)coords[y][x].x);
				x++;
			}
			y++;
		}
				// printf("%d, %d\n", master.ylen, master.xlen);
		//		printf("(%d, %d) |\n", coords[1][1].y, coords[1][1].x);
		y = 0;
		while(y < master.ylen)
		{
			x = 0;
			while (x < master.xlen)
			{
				//printf("(%d, %d) |\n", coords[y][x].y, coords[y][x].x);
				//printf("(%d, %d)\n", (int)coords[y][x].y, (int)coords[y][x].x);
				// printf("(%d, %d)\n\n", (int)coords[y+1][x+1].y, (int)coords[y+1][x+1].x);
				//draw(&master, coords, y, x, y + 1, x + 1);
				// if (x < (master.xlen)-1 && y < (master.ylen)-1)
				// {
				 	// draw(&master, coords, y, x, y + 1, x + 1);
				// }
				if (x < (master.xlen)-1){
					draw(&master, coords, y, x, y, x + 1);
					printf("p1(%d, %d) p2(%d, %d)\n", (int)coords[y][x].y, (int)coords[y][x].x, (int)coords[y][x+1].y, (int)coords[y][x+1].x);
					}
				if (y < (master.ylen)-1){
					draw(&master, coords, y, x, y + 1, x);
					printf("p1(%d, %d) p2(%d, %d)\n\n", (int)coords[y][x].y, (int)coords[y][x].x, (int)coords[y+1][x].y, (int)coords[y+1][x].x);
					//printf("(%d, %d)\n\n", (int)coords[y][x].y, (int)coords[y+1][x].x);
					}
				
				x++;
			}
			y++;
		}
		//draw(&master, coords, y, x, y+1, x);
		ft_putchar('\n');
		// printf("x%d, xend %d\n", x, master.wsize / (master.xlen + 1) * master.xlen);
		// printf("y%d, yend%d\n", y, master.wsize / (master.ylen + 1) * master.ylen);
		mlx_hook(master.win, 2, 0, my_key_funct, &master); //much faster //master or master->win as last var
		mlx_loop(master.mlx);
	}
	return (0);
}
