#include "cub3D.h"
/*
void	print_structure(t_info *map_information)
{
	printf("x_render_size : %d\n", map_information->x_render_size);
	printf("y_render_size : %d\n", map_information->y_render_size);
	printf("path_to_the_north_texture : %s\n", map_information->path_to_the_north_texture);
	printf("path_to_the_south_texture : %s\n", map_information->path_to_the_south_texture);
	printf("path_to_the_west_texture : %s\n", map_information->path_to_the_west_texture);
	printf("path_to_the_east_texture : %s\n", map_information->path_to_the_east_texture);
	printf("path_to_the_sprite_texture : %s\n", map_information->path_to_the_sprite_texture);
	printf("f_red : %d\n", map_information->f_red);
	printf("f_green : %d\n", map_information->f_green);
	printf("f_blue : %d\n", map_information->f_blue);
	printf("c_red : %d\n", map_information->c_red);
	printf("c_green : %d\n", map_information->c_green);
	printf("c_blue : %d\n", map_information->c_blue);
}

int	start_parsing(t_info *map_information, char **map)
{
	t_list	*head;
	t_list	*now;
	char	*source_line;
	int		fd;
	int		y_map_size;
	int		x_map_size;
	int		map_index;
	int		check_count;

	map_index = 0;
	y_map_size = 0;
	x_map_size = 0;
	fd = open("../conf.cub", O_RDONLY);
	map_information = malloc(sizeof(t_info));
	reset_map_information(map_information);

	while (check_count != 13)
	{
		check_count = check_structure(map_information);
		get_next_line(fd, &source_line);
		if (*source_line != '\0')
			parse_cub(source_line, map_information);
	}
	head = ft_lstnew(NULL);
	while (get_next_line(fd, &source_line) == 1)
	{
		now = ft_lstnew((void *)source_line);
		if (ft_strlen(now->content) > x_map_size)
			x_map_size = ft_strlen(now->content);
		y_map_size++;
		ft_lstadd_back(&head, now);
	}
	map = (char **)malloc(sizeof(char *) * (y_map_size + 1));
	now = head->next;
	while (now->next)
	{
		map[map_index] = ft_strdup((char *)now->content);
		printf("%s\n", map[map_index]);
		now = now->next;
		map_index++;
	}
	printf("x_map_size : %d\n", x_map_size);
	printf("y_map_size : %d\n", y_map_size);

	return (0);
}
*/
/*
int	main(int argc, char *argv[])
{
	t_info	*map_information;
	t_list	*head;
	t_list	*now;
	char	**map;
	char	*source_line;
	int		fd;
	int		y_map_size;
	int		x_map_size;
	int		map_index;
	int		check_count;

	map_index = 0;
	y_map_size = 0;
	x_map_size = 0;
	fd = open("../conf.cub", O_RDONLY);
	map_information = malloc(sizeof(t_info));
	reset_map_information(map_information);

	while (check_count != 13)
	{
		check_count = check_structure(map_information);
		get_next_line(fd, &source_line);
		if (*source_line != '\0')
			parse_cub(source_line, map_information);
	}
	head = ft_lstnew(NULL);
	while (get_next_line(fd, &source_line) == 1)
	{
		now = ft_lstnew((void *)source_line);
		if (ft_strlen(now->content) > x_map_size)
			x_map_size = ft_strlen(now->content);
		y_map_size++;
		ft_lstadd_back(&head, now);
	}
	map = (char **)malloc(sizeof(char *) * (y_map_size + 1));
	now = head->next;
	while (now->next)
	{
		map[map_index] = ft_strdup((char *)now->content);
		printf("%s\n", map[map_index]);
		now = now->next;
		map_index++;
	}
	printf("x_map_size : %d\n", x_map_size);
	printf("y_map_size : %d\n", y_map_size);

	return (0);
}
*/

int	main(/*int argc, char *argv[]*/)
{
//	t_info	map_information;
//	char	**map;
	void	*mlx_pointer;
	void	*mlx_window;
	char	*str = "Hello World!";
	int		len = 0;
	int		fd;
	char	*line;

//	map = 0;
//	start_parsing(&map_information, map);
//	print_structure(&map_information);


	fd = open("./conf.cub", O_RDONLY);
	get_next_line(fd, &line);
	len = (int)ft_strlen(str);
	printf("len : %d\n", len);
	printf("line : %s\n", line);
	mlx_pointer = mlx_init();

	while (1)
		mlx_window = mlx_new_window(mlx_pointer, 1920, 1080, "cub3D");
	return (0);
}