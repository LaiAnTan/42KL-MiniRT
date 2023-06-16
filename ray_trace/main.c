#include "minirt.h"

// wOw actually ray-tracing!1!!11!11!!

void	free_scene(t_scene	*scene)
{
	free_cam(&scene->camera);
	free_objects(&scene->objs);
	free_light(&scene->lights);
	free_ambient(&scene->ambient);
}

void	free_mlx(t_mlx_info *mlx)
{
	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx, mlx->img.img);
	if (mlx->mlx_win)
	{
		mlx_clear_window(mlx->mlx, mlx->mlx_win);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	}
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}

int main()
{
	t_scene		scene;
	t_mlx_info	mlx;
	int			loop;


	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
	mlx.img.img = NULL;
	loop = 0;
	while (1)
	{
		printf("loop = %d\n", loop);
		set_the_scene(&scene, loop);
		get_image(&mlx.img, mlx.mlx);
		kewl_quirky_raytrace(&scene, &mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
		clean_loop(&mlx);
		free_scene(&scene);
		loop += 2;
		if (loop > HEIGHT)
			loop = -1 * HEIGHT;
	}
	mlx_loop(mlx.mlx);
}

// // single loop
// # include <unistd.h>
// int main()
// {
// 	t_scene		scene;
// 	t_mlx_info	mlx;
// 	int			loop;

// 	mlx.mlx = mlx_init();
// 	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
// 	mlx.img.img = NULL;
// 	loop = 0;
// 	set_the_scene(&scene, loop);

// 	get_image(&mlx.img, mlx.mlx);
// 	kewl_quirky_raytrace(&scene, &mlx);
// 	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
// 	clean_loop(&mlx);

// 	sleep(2);
// 	free_scene(&scene);
// 	free_mlx(&mlx);
// }

// // two loop
// # include <unistd.h>
// int main()
// {
// 	t_scene		scene;
// 	t_mlx_info	mlx;
// 	int			loop;


// 	mlx.mlx = mlx_init();
// 	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "please PLESAE DONT CRASH");
// 	mlx.img.img = NULL;
// 	loop = 0;
// 	set_the_scene(&scene, loop);

// 	int i = 2;
// 	while (i)
// 	{
// 		get_image(&mlx.img, mlx.mlx);
// 		kewl_quirky_raytrace(&scene, &mlx);
// 		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img.img, 0, 0);
// 		clean_loop(&mlx);
// 		--i;
// 	}
// 	sleep(2);
// 	free_scene(&scene);
// 	free_mlx(&mlx);
// }