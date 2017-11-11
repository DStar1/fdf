#include "fdf.h"


int	my_key_funct(int keycode, t_master *master)
{
	printf("Key event %d\n", keycode);
	int x = 300;
	int y = 300;
	
	mlx_pixel_put(master->mlx, master->win, rand()%400, rand()%400, 0xFF00FF); //use struct
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

void printpoints(int *len, int i, t_points **twodstruct)
{
	int y = 0;
	int x = 0;
	while (y < i)
	{
		x = 0;
		while (x < *len)
		{
			//printf("c: %s, z: %d | ", twodstruct[y][x].c, twodstruct[y][x].z); //trying to make a 2d struct array
			printf("(%d, %d)z=%d||", twodstruct[y][x].y, twodstruct[y][x].x, twodstruct[y][x].z);
			x++;
		}
		//printf("\n");
		free(twodstruct[y]);
		y++;
	}
}

t_points **points(char *filename){
	int		fd;
	char	*line;
	int		i;
	t_points **twodstruct; //fix to find the right val
	t_points **cpy;
	int lentmp = 0;
	int *len;
	char *tmp;

//all this is to figut out the height of the file
	int y;
	y = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
		y++;
	close(fd);
	twodstruct = (t_points**)malloc(sizeof(t_points*) * y);
//////////////////

	i = 1; //i use the tmp var for the first one at index 0
	line = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, &line); //check to see if gnl runs
	tmp = line;
	lentmp = ft_cntdelim(tmp, ' ');
	len = &lentmp; //gives a seg fault when I do *len = lentemp
	//ft_putstr(line);
	////twodstruct = (t_points**)malloc(sizeof(t_points*) * (*len) + 1); //change len to whatever length y is when you find out 
	twodstruct[0] = (t_points*)malloc(sizeof(t_points) * *len);
	znc((t_points**)twodstruct, ft_strsplit(line, ' '), len, 0);
	while ((get_next_line(fd, &line)))
	{
		twodstruct[i] = (t_points*)malloc(sizeof(t_points) * *len);
		znc((t_points**)twodstruct, ft_strsplit(line, ' '), len, i);
		i++;
	}
//	printpoints(len, i, (t_points**)&twodstruct); //passing the address for freeing
	//free(twodstruct);
	//ft_putarr(ints);

	//printf("%d\n", i);
	close(fd);
	free(line);
	return ((t_points**)twodstruct);
}









// int main()//int ac, char **av) //for some reason, doesnt work with structs if ac/av
// {
// 	// if (ac <= 1)
// 	// 	return (0);
// 	void *mlx;
// 	void *win;
// 	t_master *master;
// 		//points(av[1]);
// 		(void)ac;
// 	master->mlx = mlx_init();
// 	master->win = mlx_new_window(master->mlx, 400, 400, "mlx 42");

// /////////////////////////fun//////////////////////////
// 	// int x;
// 	// int y;
// 	// y = 50;
// 	// while (y < 150)
// 	// {
// 	// 	x = 50;
// 	// 	while (x < 150)
// 	// 	{
// 	// 		mlx_pixel_put(master->mlx, master->win, x, y, 0x00FF0FFF);
// 	// 		y++;
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// 	while (x < 250)
// 	// 	{
// 	// 		mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
// 	// 		y--;
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }


// ////////////////////writes a diagnol line to the screen//////////////////
// 	int x1 = 0;
//     int y1 = 0;
//     int x2 = 100;
//     int y2 = 250;
//     int dx = x2 - x1;
//     int dy = y2 - x1;
//     // float m = dy / dx;
//     // int j = y1;
//     // float e = m - 1;
//     // int i = 0;

// 	int p;
// 	//p = 2*dy-dx;
// 	int x = x1;
// 	int y = y1;
// 	if (dx>=dy){
// 		p = 2*dy-dx;
// 		while (x<x2)
// 		{
// 			if (p >= 0)
// 			{
// 				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
// 				y++;
// 				p = p + 2 * dy - 2 * dx;
// 			}
// 			else
// 			{
// 				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
// 				p = p + 2 * dy;
// 			}
// 			x++;
// 		}
// 	}
// 	else if (dy >= dx) 
// 	{
// 		p = 2*dx-dy;
// 		while (y<y2)
// 		{
// 			if (p >= 0)
// 			{
// 				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
// 				x++;
// 				p = p + 2 * dx - 2 * dy;
// 			}
// 			else
// 			{
// 				mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
// 				p = p + 2 * dx;
// 			}
// 			y++;
// 		}
// 	}
// 	// master->x = x;
// 	// master->y = y;
// 		//mlx_key_hook(master->win, my_key_funct, master); //slower
// 	mlx_hook(master->win, 2, 0, my_key_funct, master); //much faster //master or master->win as last var
// 		//mlx_mouse_hook(win, my_key_funct, 0);
// 	mlx_loop(master->mlx);
// }



// puts keynumber // mlx_key_hook(mlx_win_list_t *win_ptr, int (*funct_ptr)(), void *param)









void window(void *mlx, void *win)
{


////////////////////writes a diagnol line to the screen//////////////////
	int x1 = 0;
    int y1 = 0;
    int x2 = 100;
    int y2 = 250;
    int dx = x2 - x1;
    int dy = y2 - x1;

	int p;
	int x = x1;
	int y = y1;
	if (dx>=dy){
		p = 2*dy-dx;
		while (x<x2)
		{
			if (p >= 0)
			{
				mlx_pixel_put(mlx, win, x, y, 0x000FFFFF);
				y++;
				p = p + 2 * dy - 2 * dx;
			}
			else
			{
				mlx_pixel_put(mlx, win, x, y, 0x000FFFFF);
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
				mlx_pixel_put(mlx, win, x, y, 0x000FFFFF);
				x++;
				p = p + 2 * dx - 2 * dy;
			}
			else
			{
				mlx_pixel_put(mlx, win, x, y, 0x000FFFFF);
				p = p + 2 * dx;
			}
			y++;
		}
	}
	mlx_hook(win, 2, 0, my_key_funct, win); //much faster //master or master->win as last var
		//mlx_mouse_hook(win, my_key_funct, 0);

}






int main(int ac, char **av)
{
	(void)ac;
	void *mlx;
	void *win;
	t_points **coords;
	t_master *master;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "mlx 42");
	coords = points(av[1]);
	printf("%d", coords[3][3].z);
	window(mlx, win);
	mlx_loop(mlx);
	return (0);
}