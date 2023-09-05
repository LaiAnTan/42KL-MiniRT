#include "../headers/minirt.h"

void	destory_images(t_mlx_info *mlx)
{
	if (mlx->img[0].img != NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->img[0].img);
		mlx->img[0].img = NULL;
	}
	if (mlx->img[1].img != NULL)
	{
		mlx_destroy_image(mlx->mlx, mlx->img[1].img);
		mlx->img[1].img = NULL;
	}
}

void	clean_exit(t_data *data)
{
	if (data->mlx->mlx_win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
	destory_images(data->mlx);
	data->scene = scene_free(data->scene, data->mlx->mlx);
	exit(0);
}