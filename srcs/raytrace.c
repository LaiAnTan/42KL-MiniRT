# include "../headers/minirt.h"

// wOw actually ray-tracing!1!!11!11!!

void	calculate_ray_positions(double store[3], double x, double y)
{
	double	hori_fov = to_radian(HORI_FOV);
	double	verti_fov = 2 * atan((HEIGHT / WIDTH) * tan(hori_fov / 2));

	double	hori_fov_per_x = hori_fov / WIDTH;
	double	verti_fov_per_y = verti_fov / HEIGHT;

	// right coordinate
	double	x_relative_to_mid = (WIDTH / 2) - x;
	double	y_relative_to_mid = (HEIGHT / 2) - y;

	// left coordinate
	// double	x_relative_to_mid  = x - (WIDTH / 2);
	// double	y_relative_to_mid = (HEIGHT / 2) - y;

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
t_ray	*project_ray(double x, double y, t_camera *camera)
{
	double		store[3];
	t_vec3	*store_vec;
	t_vec3	*dir_vector;

	calculate_ray_positions(store, x, y);
	store_vec = vec3_init_from_array(store);
	dir_vector = vec3_normalize(store_vec);
	vec3_free(&store_vec);

	return (init_ray(vec3_dup(camera->cam_coords), dir_vector));
}

void	do_ray_stuff(double x, double y, t_scene *scene, t_mlx_info *mlx)
{
	t_light		*light;
	t_object	*closest_object_src;
	t_ray		*ray;
	double		k_val;

 //  ray projection
 //  ----------------------------------------------------------------------------

	ray = project_ray(x, y, scene->sc_cameras);

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
		light = scene->sc_lights;
		while (light)
		{
			p_from_light = get_closest_light(ray, light, scene);
			if (p_from_light == ERROR)
			{
				if (!light->next && ray->type == SHADOW)
				{
					ray->type = SHADOW;
					shadow_diffuse(ray);
				}
				light = light->next;
				continue;
			}
			else
			{
				diffuse_the_bomb(ray, light, closest_object_src);
			}
			light = light->next;
		}
	}

//  -----------------------------------------------------------------------------

	// ambient
	if (scene->sc_ambients)
		ambient_color(ray, scene->sc_ambients, closest_object_src);

//  -----------------------------------------------------------------------------
	
	calculate_result_color(ray);
	write_pixel(&mlx->img, x, y, create_trgb(ray->color));
	free_ray(&ray);

	// printf("\n");
}

void	raytrace(t_scene *scene, t_mlx_info *mlx)
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
