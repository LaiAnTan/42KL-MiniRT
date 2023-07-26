/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshi-xia <cshi-xia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:37 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/27 00:24:39 by cshi-xia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/minirt.h"

void	calculate_ray_positions(double store[3], double x, double y, double fov)
{
	double	hori_fov = to_radian(fov);
	double	verti_fov = 2 * atan((HEIGHT / WIDTH) * tan(hori_fov / 2));

	double	hori_fov_per_x = hori_fov / WIDTH;
	double	verti_fov_per_y = verti_fov / HEIGHT;

	// heads up, right hand orienation

	// use this if orienation is (0,0,1)
	// double	x_relative_to_mid = (WIDTH / 2) - x;
	// double	y_relative_to_mid = (HEIGHT / 2) - y;

	// use this if orientation is (0,0,-1)
	double	x_relative_to_mid = (WIDTH / 2) - x;
	double	y_relative_to_mid = y - (HEIGHT / 2);

	double	hori_angle = absolute(x_relative_to_mid) * hori_fov_per_x;
	double	verti_angle = absolute(y_relative_to_mid) * verti_fov_per_y;

	//  orientation is (0,0,1)
	// double	alpha = (WIDTH / 2) / (tan(hori_fov / 2));
	// orientation is (0,0,-1)
	double	alpha = - (WIDTH / 2) / (tan(hori_fov / 2));

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
	t_vec3	*dir_vector;

	calculate_ray_positions(store, x, y, camera->cam_fov);
	dir_vector = vec3_normalize(vec3_init_from_array(store), O_REPLACE);

	return (init_ray(vec3_dup(camera->cam_coords), dir_vector));
}

void	do_ray_stuff(double x, double y, t_data *data)
{
	t_light		*light;
	t_object	*closest_object_src;
	t_ray		*ray;
	double		k_val;

 //  ray projection
 //  ----------------------------------------------------------------------------

	ray = project_ray(x, y, data->scene->sc_cameras);

 //  detect collision
 //  ----------------------------------------------------------------------------

	closest_object_src = get_closest_object(ray, data->scene->sc_objs, 1, &k_val);
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
		light = data->scene->sc_lights;
		while (light)
		{
			p_from_light = get_closest_light_runner(ray, light, data->scene->sc_objs);
			if (p_from_light != ERROR)
			{
				// calculate diffuse & specular lighting
				diffuse_the_bomb(ray, light, closest_object_src);
			}
			light = light->next;
		}
	}

//  -----------------------------------------------------------------------------

	// ambient
	if (data->scene->sc_ambients)
		ambient_color(ray, data->scene->sc_ambients, closest_object_src);

//  -----------------------------------------------------------------------------
	
	calculate_result_color(ray);
	write_pixel(data->mlx->render_img, x, y, create_trgb(ray->color));
	free_ray(&ray);
}

void	switch_image(t_data *image)
{
	t_img_info	*temp;

	temp = image->mlx->cur_img;
	image->mlx->cur_img = image->mlx->render_img;
	image->mlx->render_img = temp;
}

void	raytrace(t_data *data)
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
			do_ray_stuff(x, y, data);
			x += rays_per_x;
		}
		y += rays_per_y;
	}

	switch_image(data);
}
