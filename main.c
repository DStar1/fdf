#include "fdf.h"
#include "minilibx/mlx.h"

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
	int i;
	char **tmp;

	i = 0;
	while (arr[i])
	{
		if (ft_strchr(arr[i], ';'))
		{
			tmp = ft_strsplit(arr[i], ';');
			stmp[y][i].z = ft_atoi(tmp[0]);
			stmp[y][i].c = tmp[1]; //ft_atoi(tmp[1]); //or just the string
			free(tmp);
		}
		else
			stmp[y][i].z = ft_atoi(arr[i]);
		i++;
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
			printf("c: %s, z: %d | ", twodstruct[y][x].c, twodstruct[y][x].z); //trying to make a 2d struct array
			x++;
		}
		printf("\n");
		free(twodstruct[y]);
		y++;
	}
}

int main(int ac, char **av){
	int		fd;
	char	*line;
	int		i;
	t_points *twodstruct[10];
	t_points **cpy;
	int lentmp = 0;
	int *len;
	char *tmp;
	
	i = 1; //i use the tmp var for the first one at index 0
	line = NULL;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, &line); //check to see if gnl runs
	tmp = line;
	lentmp = ft_cntdelim(tmp, ' ');
	*len = lentmp;
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
	printpoints(len, i, (t_points**)&twodstruct); //passing the address for freeing
	//free(twodstruct);
	//ft_putarr(ints);

	//printf("%d\n", i);
	close(fd);
	free(line);
	return (0);
}









// int main()
// {
// 	//void *mlx;
// 	//void *win;
// 	t_master *master;
// 	int x;
// 	int y;
// 	char c1 = "0x00FF0FFF";
// 	int c = atoi(&c1);

// 	master->mlx = mlx_init();
// 	master->win = mlx_new_window(master->mlx, 400, 400, "mlx 42");
// 	y = 50;
// 	while (y < 150)
// 	{
// 		x = 50;
// 		while (x < 150)
// 		{
// 			mlx_pixel_put(master->mlx, master->win, x, y, c);
// 			y++;
// 			x++;
// 		}
// 		y++;
// 		while (x < 250)
// 		{
// 			mlx_pixel_put(master->mlx, master->win, x, y, 0x000FFFFF);
// 			y--;
// 			x++;
// 		}
// 		y++;
// 	}
// 	master->x = x;
// 	master->y = y;
// 	//mlx_key_hook(master->win, my_key_funct, master); //slower
// 	mlx_hook(master->win, 2, 0, my_key_funct, master); //much faster //master or master->win as last var
// 	//mlx_mouse_hook(win, my_key_funct, 0);
// 	mlx_loop(master->mlx);
// 	return (0);
// }


// puts keynumber // mlx_key_hook(mlx_win_list_t *win_ptr, int (*funct_ptr)(), void *param)
