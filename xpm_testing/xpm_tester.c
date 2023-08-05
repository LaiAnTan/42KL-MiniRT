#include "xpm_extractor.h"
#include <sys/time.h>

typedef struct	s_img_temp {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_temp;

void	my_mlx_pixel_put(t_img_temp *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

size_t	ft_strlen(char *a)
{
	int i = 0;
	while (a[i])
		++i;
	return (i);
}

char	*ft_strdup(char *a)
{
	char *ret;
	int	i = 0;

	ret = malloc(sizeof(char) * ft_strlen(a) + 1);
	while (a[i])
	{
		ret[i] = a[i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}

int main()
{
	// generic mlx LMAO
	void			*mlx;
	void			*mlx_win;
	t_img_temp		img;

	t_texture		*test;
	unsigned int	store;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1250, 940, "fuck");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	test = texture_init(ft_strdup("test.xpm"), mlx);
	if (!test)
		return (0);
	printf("xlm successfully ported\n");

	// stretched
	for (int x = 0; x < 1250; ++x)
	{
		for (int y = 0; y < 940; ++y)
		{
			store = get_rgb_ui(test, ((double) x / 1250), ((double) y / 940));
			my_mlx_pixel_put(&img, x, y, store);
		}
	}

	// // repeating ig
	// int cores_x;
	// int cores_y;
	// for (int x = 0; x < 1250; ++x)
	// {
	// 	for (int y = 0; y < 940; ++y)
	// 	{
	// 		cores_x = x % test->width;
	// 		cores_y = y % test->height;
	// 		store = get_rgb_ui(test, (double) (cores_x) / test->width, (double) (cores_y) / test->height);
	// 		my_mlx_pixel_put(&img, x, y, store);
	// 	}
	// }

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	sleep(5);
}