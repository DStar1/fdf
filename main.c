#include "fdf.h"
#include "minilibx/mlx.h"
//#include "libft/libft.h"


//# define RAND_MAX 400

int	my_key_funct(int keycode, t_master *master)
{
	printf("Key event %d\n", keycode);
	int x = 300;
	int y = 300;
	
	mlx_pixel_put(master->mlx, master->win, rand()%400, rand()%400, 0xFF00FF); //use struct
	return (0);
}

t_points		*znc(char **arr, int *len)
{
	int i;
	//int intarr[2];
	char **tmp;
	t_points *stmp;

	i = 0;
	stmp = (t_points*)malloc(sizeof(t_points) * *len + 1);
	//stmp[len] = NULL;
	while (arr[i])
	{
		if (ft_strchr(arr[i], ';'))
		{
			tmp = ft_strsplit(arr[i], ';');
			stmp[i].z = ft_atoi(tmp[0]);
			stmp[i].c = tmp[1]; //ft_atoi(tmp[1]); //or just the string
		}
		else
			stmp[i].z = ft_atoi(arr[i]);
		i++;
	}
	return (stmp);
}

int main(int ac, char **av){
	int		fd;
	char	*line;
	int		i;
	//char **chars;
	//int **ints;
	//t_master **master;
	t_points **twodstruct;
	t_points **cpy;
	//int zcolr[2];
	int *len = 0;
	char *tmp;
	
	i = 0;
	line = NULL;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	get_next_line(fd, &line); //check to see if gnl runs
	tmp = line;
	*len = ft_strlen(tmp);
	twodstruct = (t_points**)malloc(sizeof(t_points*) * (*len) + 1); //change len
	cpy = twodstruct;
	while ((get_next_line(fd, &line)))
	{
		get_next_line(fd, &line);
		twodstruct[i]->next = znc(ft_strsplit(line, ' '), len);
		//printf("%d, %s\n", i, line);
		i++;
	}
	printf("%d\n", cpy[0]->next->z); //trying to make a 2d struct array
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
