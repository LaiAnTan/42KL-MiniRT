#include "minirt.h"

void	get_image(t_img_info *img_info, void *mlx)
{
	img_info->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img_info->addr = mlx_get_data_addr(img_info->img, &img_info->bits_per_pixel, 
		&img_info->line_length, &img_info->endian);
}

void	clean_loop(t_mlx_info *mlx)
{
	if (mlx->img.img != NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->img.img);
		mlx->img.img = NULL;
	}
}

void	write_pixel(t_img_info *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(t_vector *color)
{
	int	r;
	int	g;
	int	b;

	r = color->raw_matrix->stuff[0][0];
	g = color->raw_matrix->stuff[1][0];
	b = color->raw_matrix->stuff[2][0];
	// overflow checker
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;

	// underflow
	if (r < 0)
		r = 0; 
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;

	// my brother in christ, what is transparancy
	return (0 << 24 | r << 16 | g << 8 | b);
}
