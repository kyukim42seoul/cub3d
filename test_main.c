#include "test_cub3D.h"

static int	set_dest_color(t_img *img, int x, int y, int color)
{
	char	*dest;
	unsigned int		test;
	static int	cnt = 0;

	dest = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	test = (unsigned int)((y * img->size_line + x * (img->bits_per_pixel / 8)));

	if (y == 539 && x == 959)
		printf("t : %d\n", test);
	*(unsigned int *)dest = color;
	cnt++;
	return (cnt);
}

int	main()
{
	void	*mlx;
	void	*win;
	int		y = 0;
	int		x;
	int		cnt;
	t_img	img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "test_cub3D");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr  = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line, &img.endian);
	printf("%d, %d, %d\n", img.bits_per_pixel, img.size_line, img.endian);

	while (y < 540)
	{
		x = 0;
		while (x < 960)
		{
			cnt = set_dest_color(&img, x, y, 0x00FF0000);
			x++;
		} y++;
	}
	printf("%d %d %d\n", y, x, cnt);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
