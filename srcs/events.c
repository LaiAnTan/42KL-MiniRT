#include "../headers/minirt.h"

int	keypress_event(int key_symbol, t_data *data)
{
	if (key_symbol == 0xff1b) // escape
	{
		printf("ESC pressed, exiting...");
		mlx_destroy_window(data->mlx->mlx, data->mlx->mlx_win);
		mlx_destroy_display(data->mlx->mlx);
		scene_free(data->scene);
		exit(0);
	}
	return (0);
}