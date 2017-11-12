#include "fdf.h"

int	my_key_funct(int keycode, t_master *master)
{
	printf("Key event %d\n", keycode);
	// int x = 300;
	// int y = 300;
	if (keycode == 53)
		exit(1);
	mlx_pixel_put(master->mlx, master->win, rand()%400, rand()%400, 16711935);//0xFF00FF); //use struct
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

void printpoints(int xlen, int ylen, t_points **twodstruct)
{
	int y = 0;
	int x = 0;
	while (y < ylen)
	{
		x = 0;
		while (x < xlen)
		{
			//printf("c: %s, z: %d | ", twodstruct[y][x].c, twodstruct[y][x].z); //trying to make a 2d struct array
			printf("(%d, %d)z=%d||", twodstruct[y][x].y, twodstruct[y][x].x, twodstruct[y][x].z);
			x++;
		}
		printf("\n");
		free(twodstruct[y]);
		y++;
	}
	free(twodstruct);
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
	twodstruct = (t_points**)malloc(sizeof(t_points*) * y);
//////////////////

	y = 1; //y use the tmp var for the first one at index 0
	line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, &line); //check to see if gnl runs
	tmp = line;
	master->xlen = ft_cntdelim(tmp, ' ');
	twodstruct[0] = (t_points*)malloc(sizeof(t_points) * master->xlen);
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

void draw(t_master *master, t_points **coords, int y1, int x1, int y2, int x2)
{
////////////////////writes line to the screen//////////////////
	// int x1 = 0;
    // int y1 = 0;
    // int x2 = 100;
    // int y2 = 250;
	//int x2;
    //int y2;
	//x2 = coords[y1][x1 + 1].x;
	//ft_putnbr(x2);
	//ft_putchar('\n');
	//x2 = x2 * 10;
	//y2 = y1; //coords[y1][x1];
	// x1 = 0;
    // y1 = 100;
    // x2 = 0;
    // y2 = 200;
	// x1 = 0;
	// y1 = 100;
	// x2 = 100;
	// y2 = 100;
    int dx = x2 - x1;
    int dy = y2 - x1;
				//printf("%d,%d,%d,%d\n", y, x, y, x + 100);
	int p;
	int x = x1;
	int y = y1;
	if (y1 == y2) //straight horizontal line
	{
		while (x < x2)
		{
			mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
			x++;
		}
	}
	else if (x1 == x2) //straight vertical line
	{
		while (y < y2)
		{
			mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
			y++;
		}
	}
	else if (dx>=dy){
		p = 2*dy-dx;
		while (x<x2)
		{
			if (p >= 0)
			{
				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
				y++;
				p = p + 2 * dy - 2 * dx;
			}
			else
			{
				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
				p = p + 2 * dy;
			}
			x++;
		}
	}
	else if (dy >= dx) 
	{
		p = 2*dx-dy;
		while (y<y2)
		{
			if (p >= 0)
			{
				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
				x++;
				p = p + 2 * dx - 2 * dy;
			}
			else
			{
				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
				p = p + 2 * dx;
			}
			y++;
		}
	}
	return ;
}

int main(int ac, char **av)
{
	t_points **coords;
	t_master master;
	int x;
	int y;
	master.wsize = 1000;
	
	if (ac == 2)
	{
		//master.xlen = 0;
		master.ylen = 0;
		coords = points(av[1], &master);
		master.mlx = mlx_init();
		master.win = mlx_new_window(master.mlx, master.wsize, master.wsize, av[1]);
		//adjust all coordinates to fit the screen equally
		// master.ylen = 8;
		// master.xlen = 6;
		y = (master.wsize / (master.ylen + 1));
		while(y <= master.wsize / (master.ylen + 1) * (master.ylen))
		{
			x = (master.wsize / (master.xlen + 1));
			while (x <= master.wsize / (master.xlen + 1) * (master.xlen))
			{
				if (x < master.wsize / (master.xlen + 1) * (master.xlen))
					draw(&master, coords, y, x, y, x + (master.wsize / (master.xlen + 1)));
				if (y < master.wsize / (master.ylen + 1) * (master.ylen))
					draw(&master, coords, y, x, y + (master.wsize / (master.ylen + 1)), x);
				x += (master.wsize / (master.xlen + 1));
			}
			y += (master.wsize / (master.ylen + 1));
		}
		// printf("x%d, xend %d\n", x, master.wsize / (master.xlen + 1) * master.xlen);
		// printf("y%d, yend%d\n", y, master.wsize / (master.ylen + 1) * master.ylen);
		mlx_hook(master.win, 2, 0, my_key_funct, &master); //much faster //master or master->win as last var
		mlx_loop(master.mlx);
	}
	//return (0);
}