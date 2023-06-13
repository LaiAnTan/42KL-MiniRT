#include "minirt.h"

// wOw actually ray-tracing!1!!11!11!!

void	calculate_ray_positions(double store[3], double x, double y)
{
	double	hori_fov = to_radian(HORI_FOV);
	double	verti_fov = 2 * atan((HEIGHT / WIDTH) * tan(hori_fov / 2));

	double	hori_fov_per_x = hori_fov / WIDTH;
	double	verti_fov_per_y = verti_fov / HEIGHT;

	double	x_relative_to_mid  = x - (WIDTH / 2);
	double	y_relative_to_mid = (HEIGHT / 2) - y;

	double	hori_angle = absolute(x_relative_to_mid) * hori_fov_per_x;
	double	verti_angle = absolute(y_relative_to_mid) * verti_fov_per_y;

	double	alpha = (WIDTH / 2) / (tan(hori_fov / 2));

	double	acc_x = alpha * tan(hori_angle);
	if (x_relative_to_mid < 0)
		acc_x *= -1;

	double	acc_y = alpha * tan(verti_angle);
	if (y_relative_to_mid < 0)
		acc_y *= -1;

	double	acc_z = alpha;

	store[0] = acc_x;
	store[1] = acc_y; 
	store[2] = acc_z;
}

// projects a ray
t_ray	*project_ray(double x, double y, t_cam *camera)
{
	double		store[3];
	t_vector	*store_vec;
	t_vector	*dir_vector;

	calculate_ray_positions(store, x, y);
	store_vec = init_vector_intarr(store);
	dir_vector = v_get_unit_v(store_vec);
	free_vector(&store_vec);

	return (init_ray(dup_vct(camera->position), dir_vector));
}

void	do_ray_stuff(double x, double y, t_scene *scene, t_mlx_info *mlx)
{
	t_light		*light;
	t_objects	*closest_object_src;
	t_ray		*ray;
	double		k_val;

 //  ray projection
 //  ----------------------------------------------------------------------------

	ray = project_ray(x, y, scene->camera);

 //  detect collision
 //  ----------------------------------------------------------------------------

	closest_object_src = get_closest_object(ray, scene, 1, &k_val);
	if (closest_object_src)
	{
		move_ray(ray, k_val);
		ray->type = COLLIDED;
	}

 //  detect light source
 //  ----------------------------------------------------------------------------

	double		p_from_light;

	if (ray->type == COLLIDED)
	{
		ray->type = SHADOW;
		light = scene->lights;
		while (light)
		{
			p_from_light = get_closest_light(ray, light, scene);
			if (p_from_light == ERROR)
			{
				if (!light->next && ray->type == SHADOW)
				{
					// is a shadow ray
					ray->type = SHADOW;
					shadow_diffuse(ray);
				}
				light = light->next;
				continue;
			}
			else
			{
				// calculate diffuse lighting
				ray->type = COLLIDED;
				diffuse_the_bomb(ray, light, closest_object_src);
			}
			light = light->next;
		}
	}

//  -----------------------------------------------------------------------------

	// ambient
	ambient_color(ray, scene->ambient, closest_object_src);

//  -----------------------------------------------------------------------------
	
	calculate_result_color(ray);
	write_pixel(&mlx->img, x, y, create_trgb(ray->color));
	free_ray(&ray);

	// printf("\n");
}

void	kewl_quirky_raytrace(t_scene *scene, t_mlx_info *mlx)
{
	double	x;
	double	y;
	double	rays_per_x = WIDTH / RAYS_IN_X;
	double	rays_per_y = HEIGHT / RAYS_IN_Y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			do_ray_stuff(x, y, scene, mlx);
			x += rays_per_x;
		}
		y += rays_per_y;
	}
}

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